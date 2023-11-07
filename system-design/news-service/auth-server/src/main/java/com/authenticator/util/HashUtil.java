package com.authenticator.util;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;
import java.util.Random;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class HashUtil {
    @Value("${HASH_ITERATIONS_LIMIT}")
    private int hashIterationsLimitTemp;

    private static int HASH_ITERATIONS_LIMIT;

    @Value("${HASH_PEPPER}")
    private String hashPepperTemp;

    private static String HASH_PEPPER;

    @Value("${HASH_ITERATIONS_LIMIT}")
    public void setHashIterationsLimit(final int hashIterationsLimit) {
        HASH_ITERATIONS_LIMIT = hashIterationsLimit;
    }

    @Value("${HASH_PEPPER}")
    public void setHashPepper(final String hashPepper) {
        HASH_PEPPER = hashPepper;
    }

    public static String getEncryptedString(final String s) throws Exception {
        String result = s;
        for (int i = 0; i < HASH_ITERATIONS_LIMIT; i += 1) {
            result = getStringWithSaltAndPepper(result);
            result = getStringWithEncryptionAlgorithm(result);
        }
        return result;
    }

    private static String getStringWithSaltAndPepper(final String s) {
        // TODO store random salt to database
        // return getSalt() + s + HASH_PEPPER;
        return s + HASH_PEPPER;
    }

    private static String getSalt() {
        final Random r = new SecureRandom();
        final byte[] salt = new byte[64];
        r.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt).substring(2, 10);
    }

    private static String getStringWithEncryptionAlgorithm(final String s) throws Exception {
        final MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.reset();
        md.update(s.getBytes("utf8"));
        return String.format("%0128x", new BigInteger(1, md.digest()));
    }
}
