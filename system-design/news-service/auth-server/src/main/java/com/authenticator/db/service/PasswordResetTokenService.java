package com.authenticator.db.service;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.authenticator.db.entity.PasswordResetToken;
import com.authenticator.db.repository.PasswordResetTokenRepository;

@Service
public class PasswordResetTokenService {
    private final PasswordResetTokenRepository passwordResetTokenRepository;

    @Autowired
    public PasswordResetTokenService(final PasswordResetTokenRepository repository) {
        this.passwordResetTokenRepository = repository;
    }

    public void save(final PasswordResetToken passwordResetToken) {
        this.passwordResetTokenRepository.save(passwordResetToken);
    }

    public void delete(final PasswordResetToken passwordResetToken) {
        this.passwordResetTokenRepository.delete(passwordResetToken);
    }

    public Optional<PasswordResetToken> getPasswordResetTokenByToken(final String token) {
        return this.passwordResetTokenRepository.findByToken(token);
    }

    public Optional<PasswordResetToken> getPasswordResetTokenByUserID(final Integer userID) {
        return this.passwordResetTokenRepository.findByUserId(userID);
    }
}