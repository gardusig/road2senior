package com.authenticator.db.repository;

import java.util.Optional;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import com.authenticator.db.entity.UserToken;

@Repository
public interface UserTokenRepository extends CrudRepository<UserToken, Integer> {
    Optional<UserToken> findByToken(final String token);
}