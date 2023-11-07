package com.authenticator.model;

public class LoginResponse {
    private final String token;

    public LoginResponse(final String token) {
        this.token = token;
    }

    public String getToken() {
        return this.token;
    }
}