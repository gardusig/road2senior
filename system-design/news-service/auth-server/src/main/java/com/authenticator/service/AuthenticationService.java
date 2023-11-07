package com.authenticator.service;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.authenticator.db.entity.PasswordResetToken;
import com.authenticator.db.entity.User;
import com.authenticator.db.entity.UserRole;
import com.authenticator.db.entity.UserToken;
import com.authenticator.db.service.PasswordResetTokenService;
import com.authenticator.db.service.UserService;
import com.authenticator.db.service.UserTokenService;
import com.authenticator.model.ValidateResponse;
import com.authenticator.util.HashUtil;
import com.authenticator.util.PasswordValidationUtil;
import com.authenticator.util.TimeUtil;
import com.authenticator.util.TokenUtil;

@Service
public class AuthenticationService {
    private static final int PASSWORD_MAX_WRONG_ATTEMPTS = 5;
    private static final long TOKEN_EXPIRATION_MILLISECONDS = TimeUtil.getMillisecondsFromMinutes(15);
    private static final long PASSWORD_EXPIRATION_MILLISECONDS = TimeUtil.getMillisecondsFromFromDays(90);

    private final UserService userService;
    private final UserTokenService userTokenService;
    private final PasswordResetTokenService passwordResetTokenService;

    @Autowired
    public AuthenticationService(final UserService userService, final UserTokenService userTokenService,
            final PasswordResetTokenService passwordResetTokenService) {
        this.userService = userService;
        this.userTokenService = userTokenService;
        this.passwordResetTokenService = passwordResetTokenService;
    }

    public User getUser(final String email) {
        return this.userService.getUserByEmail(email).get();
    }

    public Boolean hasUserWithEmail(final String email) {
        return this.userService.getUserByEmail(email).isPresent();
    }

    public ValidateResponse hasPasswordResetToken(final String email, final String token) {
        final Optional<PasswordResetToken> passwordResetTokenOptional = this.passwordResetTokenService
                .getPasswordResetTokenByToken(token);
        if (passwordResetTokenOptional.isEmpty()) {
            return new ValidateResponse("token not found");
        }
        if (!passwordResetTokenOptional.get().getUser().getEmail().equals(email)) {
            return new ValidateResponse("token not found");
        }
        return new ValidateResponse();
    }

    public ValidateResponse validatePasswordResetToken(final String email, final String token) {
        return TokenUtil.isTokenValid(token, email);
    }

    public ValidateResponse resetPassword(final String email, final String newPassword) throws Exception {
        final ValidateResponse validatePasswordResponse = PasswordValidationUtil.isPasswordValid(newPassword);
        if (validatePasswordResponse.hasError()) {
            return validatePasswordResponse;
        }
        final User user = this.getUser(email);
        user.setPassword(HashUtil.getEncryptedString(newPassword));
        user.setConsecutiveWrongAttempts(0);
        user.setPasswordLastUpdatedAt(TimeUtil.getCurrentTimestamp());
        this.userService.save(user);
        return new ValidateResponse();
    }

    public ValidateResponse isUserAuthorized(final String email, final String password) throws Exception {
        final User user = this.getUser(email);
        if (user.getConsecutiveWrongAttempts() >= PASSWORD_MAX_WRONG_ATTEMPTS) {
            return new ValidateResponse("too many wrong password attempts");
        }
        final Optional<String> userPassword = Optional.ofNullable(user.getPassword());
        if (userPassword.isEmpty()) {
            return new ValidateResponse("user without registered password");
        }
        final String encryptedPassword = HashUtil.getEncryptedString(password);
        if (!userPassword.get().equals(encryptedPassword)) {
            this.receiveWrongPasswordAttempt(user);
            return new ValidateResponse("wrong password");
        }
        this.receiveCorrectPasswordAttempt(user);
        if (isUserPasswordExpired(user.getPasswordLastUpdatedAt())) {
            return new ValidateResponse("password expired");
        }
        return new ValidateResponse();
    }

    public static Boolean isUserPasswordExpired(final Timestamp lastUpdatedAt) {
        final Timestamp currentTimestamp = TimeUtil.getCurrentTimestamp();
        final long diffInMilliseconds = currentTimestamp.getTime() - lastUpdatedAt.getTime();
        return diffInMilliseconds > PASSWORD_EXPIRATION_MILLISECONDS;
    }

    public String getPasswordResetToken(final String email) {
        final User user = this.getUser(email);
        this.userService.save(user);
        final Time expirationTime = TimeUtil.getCurrentTimeWithAdditionalTime(TOKEN_EXPIRATION_MILLISECONDS);
        final String fullToken = TokenUtil.generateTokenWithEmail(user.getEmail(), expirationTime);
        final String token = fullToken.substring(fullToken.length() - 8);
        final Optional<PasswordResetToken> passwordResetTokenOptional = passwordResetTokenService
                .getPasswordResetTokenByUserID(user.getId());
        final PasswordResetToken passwordResetToken;
        if (passwordResetTokenOptional.isPresent()) {
            passwordResetToken = passwordResetTokenOptional.get();
        } else {
            passwordResetToken = new PasswordResetToken();
            passwordResetToken.setUser(user);
        }
        passwordResetToken.setToken(token);
        this.passwordResetTokenService.save(passwordResetToken);
        return token;
    }

    public ValidateResponse isUserAllowed(final String email) {
        final User user = this.getUser(email);
        if (!user.getEnabled()) {
            return new ValidateResponse("user disabled");
        }
        final UserRole userRole = user.getUserRole();
        final ValidateResponse isCurrentTimeAllowedForUserRoleResponse = isCurrentTimeAllowedForUserRole(userRole);
        if (isCurrentTimeAllowedForUserRoleResponse.hasError()) {
            return isCurrentTimeAllowedForUserRoleResponse;
        }
        return new ValidateResponse();
    }

    public String generateToken(final String email) {
        final User user = this.getUser(email);
        final Time expirationTime = user.getUserRole().getAllowedFinishTime();
        final String token = TokenUtil.generateTokenWithEmail(email, expirationTime);
        final UserToken userToken = new UserToken();
        userToken.setUser(user);
        userToken.setToken(token);
        userTokenService.save(userToken);
        return token;
    }

    public ValidateResponse validateToken(final String email, final String token, final String strategyOperationName) {
        final ValidateResponse isTokenValidResponse = isTokenValid(email, token);
        if (isTokenValidResponse.hasError()) {
            return isTokenValidResponse;
        }
        // TODO -> validate operation for user token
        // final Optional<StrategyOperation> strategyOperation =
        // this.strategyOperationService
        // .getStrategyOperationByName(strategyOperationName);
        // if (strategyOperation.isEmpty()) {
        // return new ValidateResponse("unknown operation");
        // }
        // final User user = this.getUser(email);
        // if
        // (!user.getUserRole().getStrategyOperation().contains(strategyOperation.get()))
        // {
        // return new ValidateResponse("operation not valid for user");
        // }
        return new ValidateResponse();
    }

    public ValidateResponse logout(final String email, final String token) {
        final ValidateResponse isTokenValidResponse = isTokenValid(email, token);
        if (isTokenValidResponse.hasError()) {
            return isTokenValidResponse;
        }
        final UserToken userToken = this.userTokenService.getUserToken(token).get();
        this.userTokenService.delete(userToken);
        return new ValidateResponse();
    }

    public ValidateResponse createNewUser(final String name, final String email) {
        if (hasUserWithEmail(email)) {
            return new ValidateResponse("user already created");
        }
        final User user = new User();
        user.setName(name);
        user.setEmail(email);
        final UserRole userRole = new UserRole();
        // TODO remove hard coded user role
        userRole.setId(1);
        user.setUserRole(userRole);
        this.userService.save(user);
        return new ValidateResponse();
    }

    public ValidateResponse deleteUser(final String email) {
        final User user;
        try {
            user = this.getUser(email);
        } catch (final Exception e) {
            return new ValidateResponse("user not found");
        }
        // final PasswordResetToken passwordResetToken = user.getPasswordResetToken();
        // if (passwordResetToken != null) {
        // this.passwordResetTokenService.delete(passwordResetToken);
        // }
        this.userService.delete(user);
        return new ValidateResponse();
    }

    private ValidateResponse isTokenValid(final String email, final String token) {
        final ValidateResponse isTokenValidResponse = TokenUtil.isTokenValid(token, email);
        if (isTokenValidResponse.hasError()) {
            return isTokenValidResponse;
        }
        final Optional<UserToken> userTokenOptional = this.userTokenService.getUserToken(token);
        if (userTokenOptional.isEmpty()) {
            return new ValidateResponse("token not found");
        }
        return new ValidateResponse();
    }

    private void receiveWrongPasswordAttempt(final User user) {
        final Integer previous = user.getConsecutiveWrongAttempts();
        user.setConsecutiveWrongAttempts(previous + 1);
        this.userService.save(user);
    }

    private void receiveCorrectPasswordAttempt(final User user) {
        user.setConsecutiveWrongAttempts(0);
        this.userService.save(user);
    }

    private ValidateResponse isCurrentTimeAllowedForUserRole(final UserRole userRole) {
        final Time currentTime = TimeUtil.getCurrentTime();
        if (currentTime.compareTo(userRole.getAllowedStartTime()) < 0) {
            return new ValidateResponse("too early login request for user role");
        }
        if (currentTime.compareTo(userRole.getAllowedFinishTime()) > 0) {
            return new ValidateResponse("too late login request for user role");
        }
        return new ValidateResponse();
    }
}