package br.com.news.provider.news.model;

public class NewsRequestResponseModel {
    private String status;
    private Integer totalResults;
    private NewsArticleModel[] articles;

    public String getStatus() {
        return this.status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Integer getTotalResults() {
        return this.totalResults;
    }

    public void setTotalResults(Integer totalResults) {
        this.totalResults = totalResults;
    }

    public NewsArticleModel[] getArticles() {
        return this.articles;
    }

    public void setArticles(NewsArticleModel[] articles) {
        this.articles = articles;
    }
}
