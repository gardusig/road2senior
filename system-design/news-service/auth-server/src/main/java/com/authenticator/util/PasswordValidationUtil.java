package com.authenticator.util;

import java.util.HashSet;
import java.util.Set;

import org.springframework.stereotype.Component;

import com.authenticator.model.ValidateResponse;

@Component
public class PasswordValidationUtil {
    private static final int PASSWORD_MIN_SATISFIED_CONDITIONS = 4;
    private static final int PASSWORD_MIN_LENGTH = 6;

    public static ValidateResponse isPasswordValid(final String password) {
        if (password.length() < PASSWORD_MIN_LENGTH) {
            return new ValidateResponse("password should have at least " + PASSWORD_MIN_LENGTH + " characters");
        }
        final Set<Integer> satisfiedConditions = new HashSet<>();
        for (int i = 0; i < password.length(); i += 1) {
            final Character c = password.charAt(i);
            if (Character.isUpperCase(c)) {
                satisfiedConditions.add(0);
            } else if (Character.isLowerCase(c)) {
                satisfiedConditions.add(1);
            } else if (Character.isDigit(c)) {
                satisfiedConditions.add(2);
            } else {
                satisfiedConditions.add(3);
            }
        }
        if (satisfiedConditions.size() < PASSWORD_MIN_SATISFIED_CONDITIONS) {
            return new ValidateResponse(
                    "password should have at least " + PASSWORD_MIN_SATISFIED_CONDITIONS + " character types");
        }
        return new ValidateResponse();
    }
}