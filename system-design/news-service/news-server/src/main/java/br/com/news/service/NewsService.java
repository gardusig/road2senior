package br.com.news.service;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import br.com.news.db.entity.ReadLater;
import br.com.news.db.service.ReadLaterService;
import br.com.news.provider.news.model.NewsArticleModel;
import br.com.news.provider.news.model.NewsSourceModel;

@Service
public class NewsService {
    private final ReadLaterService readLaterService;

    @Autowired
    public NewsService(final ReadLaterService readLaterService) {
        this.readLaterService = readLaterService;
    }

    public void addReadLater(final Integer userId, final NewsArticleModel article) {
        final ReadLater readLater = getReadLaterFromArticle(article);
        readLater.setUserId(userId);
        this.readLaterService.add(readLater);
    }

    public void deleteReadLater(final Integer userId, final String url) {
        this.readLaterService.delete(userId, url);
    }

    public List<NewsArticleModel> query(final Integer userId) throws Exception {
        final List<NewsArticleModel> articles = new ArrayList<>();
        for (final ReadLater readLater : this.readLaterService.query(userId)) {
            articles.add(getArticleFromReadLater(readLater));
        }
        return articles;
    }

    private ReadLater getReadLaterFromArticle(final NewsArticleModel article) {
        final ReadLater readLater = new ReadLater();
        readLater.setAuthor(article.getAuthor());
        readLater.setContent(article.getContent());
        readLater.setDescription(article.getDescription());
        readLater.setPublishedAt(article.getPublishedAt());
        readLater.setSourceId(article.getSource().getId());
        readLater.setSourceName(article.getSource().getName());
        readLater.setTitle(article.getTitle());
        readLater.setUrl(article.getUrl());
        readLater.setUrlToImage(article.getUrlToImage());
        return readLater;
    }

    private NewsArticleModel getArticleFromReadLater(final ReadLater readLater) {
        final NewsArticleModel article = new NewsArticleModel();
        article.setAuthor(readLater.getAuthor());
        article.setContent(readLater.getContent());
        article.setDescription(readLater.getDescription());
        article.setPublishedAt(readLater.getPublishedAt());
        final NewsSourceModel source = new NewsSourceModel();
        source.setId(readLater.getSourceId());
        source.setName(readLater.getSourceName());
        article.setSource(source);
        article.setTitle(readLater.getTitle());
        article.setUrl(readLater.getUrl());
        article.setUrlToImage(readLater.getUrlToImage());
        return article;
    }
}