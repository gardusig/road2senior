package br.com.news.provider.auth;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

@Component
public class AuthProviderApiUtil {
    @Value("${AUTH_API_HOST}")
    private String authApiHostTemp;
    private static String AUTH_API_HOST;

    @Value("${AUTH_API_ENDPOINT}")
    private String authApitEndpointTemp;
    private static String AUTH_API_ENDPOINT;

    @Value("${AUTH_API_HOST}")
    public void setAuthApiHost(final String authApiHost) {
        AUTH_API_HOST = authApiHost;
    }

    @Value("${AUTH_API_ENDPOINT}")
    public void setAuthApitEndpoint(final String authApitEndpoint) {
        AUTH_API_ENDPOINT = authApitEndpoint;
    }

    public static Optional<Integer> getUserIdFromToken(final String email, final String token, final String op) {
        final String url = getProviderURL(email, token, op);
        final String response = new RestTemplate().getForObject(url, String.class);
        try {
            return Optional.of(Integer.valueOf(response));
        } catch (final Exception e) {
            return null;
        }
    }

    private static String getProviderURL(final String email, final String token, final String op) {
        return AUTH_API_HOST + String.format(AUTH_API_ENDPOINT, email, token, op);
    }
}