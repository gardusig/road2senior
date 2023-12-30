package aoc.client;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URI;
import java.io.IOException;
import java.util.stream.Stream;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Client {
    private static String DEFAULT_BASE_URL = "https://adventofcode.com";

    private static final Logger logger = LoggerFactory.getLogger(Client.class);

    private final OkHttpClient httpClient;
    private final int year;
    private final int day;
    private final URI baseUri;

    private String sessionToken;

    public Client(final String baseUrl, final int year, final int day) {
        this.httpClient = new OkHttpClient();
        this.baseUri = URI.create(baseUrl);
        this.year = year;
        this.day = day;
        // TODO refresh session token
    }

    public Client(final int year, final int day) {
        this(DEFAULT_BASE_URL, year, day);
    }

    public Stream<String> getInput() {
        try {
            var response = this.httpClient.newCall(
                    generateInputHttpRequest())
                    .execute();
            try {
                if (response.isSuccessful()) {
                    var reader = new BufferedReader(
                            new InputStreamReader(
                                    response.body().byteStream()));
                    return reader.lines();
                }
                logger.error("Error fetching input data. HTTP status code: {}", response.code());
            } finally {
                response.close();
            }
        } catch (IOException e) {
            logger.error("Error fetching input data due to IOException", e);
        } catch (Exception e) {
            logger.error("Error fetching input data", e);
        }
        return Stream.empty();
    }

    private String generateInputUrlFormat() {
        String path = String.format("%d/day/%d/input", this.year, this.day);
        return baseUri.resolve(path).toString();
    }

    private Request generateInputHttpRequest() {
        return new Request.Builder()
                .url(generateInputUrlFormat())
                .header("Cookie", "session=" + sessionToken)
                .build();
    }
}
