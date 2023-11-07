package com.authenticator.model;

import java.util.Optional;

public class ValidateResponse {
    private final Optional<String> errorMessage;

    public ValidateResponse() {
        errorMessage = Optional.empty();
    }

    public ValidateResponse(final String errorMessage) {
        this.errorMessage = Optional.ofNullable(errorMessage);
    }

    public Boolean hasError() {
        return this.errorMessage.isPresent();
    }

    public String getErrorMessage() {
        return this.errorMessage.get();
    }
}