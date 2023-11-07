package com.authenticator.db.service;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.authenticator.db.entity.User;
import com.authenticator.db.repository.UserRepository;

@Service
public class UserService {
    private final UserRepository userRepository;

    @Autowired
    public UserService(final UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public Optional<User> getUserByEmail(final String email) {
        return this.userRepository.findByEmail(email);
    }

    public void save(final User user) {
        this.userRepository.save(user);
    }

    public void delete(final User user) {
        this.userRepository.delete(user);
    }
}