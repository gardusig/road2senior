package com.authenticator.util;

import com.authenticator.model.ValidateResponse;

import java.sql.Time;
import java.util.Date;
import java.util.function.Function;

import org.springframework.stereotype.Component;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;

@Component
public class TokenUtil {
    private static final String SECRET = "$H@nD-P1ck3D-S3cr3T-3ncrypT-K3Y$";

    public static ValidateResponse isTokenValid(final String token, final String email) {
        final ValidateResponse isTokenEmailValidResponse = TokenUtil.isTokenEmailValid(token, email);
        if (isTokenEmailValidResponse.hasError()) {
            return isTokenEmailValidResponse;
        }
        final ValidateResponse isTokenExpiredResponse = TokenUtil.isTokenExpired(token);
        if (isTokenExpiredResponse.hasError()) {
            return isTokenExpiredResponse;
        }
        return new ValidateResponse();
    }

    public static String generateTokenWithEmail(final String email, final Time expirationTime) {
        return TokenUtil.generateToken(email, expirationTime);
    }

    private static String generateToken(final String subject, final Time expirationTime) {
        final Date issuedAt = TimeUtil.getCurrentDate();
        final Date expiresAt = TimeUtil.getCurrentDateWithTime(expirationTime);
        return Jwts.builder().setSubject(subject).setIssuedAt(issuedAt).setExpiration(expiresAt)
                .signWith(SignatureAlgorithm.HS512, TokenUtil.SECRET).compact();
    }

    private static ValidateResponse isTokenEmailValid(final String token, final String email) {
        final String tokenEmail;
        try {
            tokenEmail = TokenUtil.getSubjectFromToken(token);
        } catch (final Exception e) {
            return new ValidateResponse("failed to extract email from token");
        }
        if (!email.equals(tokenEmail)) {
            return new ValidateResponse("given email differs from token email");
        }
        return new ValidateResponse();
    }

    private static ValidateResponse isTokenExpired(final String token) {
        final Date nowDate = TimeUtil.getCurrentDate();
        final Date expirationDate = TokenUtil.getExpirationDateFromToken(token);
        if (nowDate.after(expirationDate)) {
            return new ValidateResponse("token expired");
        }
        return new ValidateResponse();
    }

    private static String getSubjectFromToken(final String token) {
        return TokenUtil.getClaimFromToken(token, Claims::getSubject);
    }

    private static Date getExpirationDateFromToken(final String token) {
        return TokenUtil.getClaimFromToken(token, Claims::getExpiration);
    }

    private static <T> T getClaimFromToken(final String token, final Function<Claims, T> claimsResolver) {
        final Claims claims = TokenUtil.getAllClaimsFromToken(token);
        return claimsResolver.apply(claims);
    }

    private static Claims getAllClaimsFromToken(final String token) {
        return Jwts.parser().setSigningKey(TokenUtil.SECRET).parseClaimsJws(token).getBody();
    }
}