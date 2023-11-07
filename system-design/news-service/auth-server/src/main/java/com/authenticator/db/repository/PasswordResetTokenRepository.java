package com.authenticator.db.repository;

import java.util.Optional;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import com.authenticator.db.entity.PasswordResetToken;

@Repository
public interface PasswordResetTokenRepository extends CrudRepository<PasswordResetToken, Integer> {
    Optional<PasswordResetToken> findByUserId(final Integer UserID);

    Optional<PasswordResetToken> findByToken(final String token);
}