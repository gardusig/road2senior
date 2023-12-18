package aoc.client;

import okhttp3.mockwebserver.MockResponse;
import okhttp3.mockwebserver.MockWebServer;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

public class ClientTest {
    private Client client;
    private MockWebServer server;

    @BeforeEach
    void setUp() {
        server = new MockWebServer();
        client = new Client(server.url("").toString(), 0, 0);
    }

    @AfterEach
    void tearDown() throws Exception {
        server.shutdown();
    }

    @Test
    void testGetInput() throws Exception {
        server.enqueue(new MockResponse().setBody("input line 1\ninput line 2"));
        try (Stream<String> input = client.getInput()) {
            var request = server.takeRequest();
            assertEquals("/0/day/0/input", request.getPath());
            assertEquals("GET", request.getMethod());
            assertEquals("session=null", request.getHeader("Cookie"));
            List<String> inputList = input.collect(Collectors.toList());
            assertNotNull(inputList);
            assertEquals(2, inputList.size());
            assertEquals("input line 1", inputList.get(0));
            assertEquals("input line 2", inputList.get(1));
        }
    }
}
