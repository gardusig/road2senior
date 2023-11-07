package com.authenticator.model;

public class LoginRequest {
    private String email;
    private String password;

    public LoginRequest(String email, String password) throws Exception {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return this.email;
    }

    public String getPassword() {
        return this.password;
    }
}