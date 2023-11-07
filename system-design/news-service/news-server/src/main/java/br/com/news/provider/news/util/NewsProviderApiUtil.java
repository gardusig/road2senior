package br.com.news.provider.news.util;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import br.com.news.provider.news.model.NewsRequestResponseModel;

@Component
public class NewsProviderApiUtil {
    @Value("${NEWS_API_KEY}")
    private String newsApiKeyTemp;
    private static String NEWS_API_KEY;

    @Value("${NEWS_API_HOST}")
    private String newsApiHostTemp;
    private static String NEWS_API_HOST;

    @Value("${NEWS_API_KEY}")
    public void setNewsApiKey(final String newsApiKey) {
        NEWS_API_KEY = newsApiKey;
    }

    @Value("${NEWS_API_HOST}")
    public void setNewsApiHost(final String newsApiHostTemp) {
        NEWS_API_HOST = newsApiHostTemp;
    }

    public static NewsRequestResponseModel getTopHeadlinesByCountry(final String country) {
        final String url = getProviderUrlWithFilter("top-headlines", "country", country);
        return getResponse(url);
    }

    public static NewsRequestResponseModel getTopHeadlinesByCategory(final String category) {
        final String url = getProviderUrlWithFilter("top-headlines", "category", category);
        return getResponse(url);
    }

    public static NewsRequestResponseModel getTopHeadlinesByQueryString(final String queryString) {
        final String url = getProviderUrlWithFilter("top-headlines", "q", queryString);
        return getResponse(url);
    }

    public static NewsRequestResponseModel getEverythingByQueryString(final String queryString) {
        final String url = getProviderUrlWithFilter("everything", "q", queryString);
        return getResponse(url);
    }

    private static String getProviderUrlWithFilter(final String endpoint, final String tag, final String value) {
        return String.format("%s&%s=%s", getProviderURL(endpoint), tag, value);
    }

    private static String getProviderURL(final String endpoint) {
        return String.format("%s/%s?apiKey=%s", NEWS_API_HOST, endpoint, NEWS_API_KEY);
    }

    private static NewsRequestResponseModel getResponse(final String url) {
        return new RestTemplate().getForObject(url, NewsRequestResponseModel.class);
    }
}