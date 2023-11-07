package br.com.news.db.repository;

import br.com.news.db.entity.ReadLater;

import java.util.List;
import java.util.Optional;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ReadLaterRepository extends CrudRepository<ReadLater, Integer> {
    void deleteByUserIdAndUrl(final Integer userId, final String url);

    List<ReadLater> findAllByUserId(final Integer userId);

    Optional<ReadLater> findByUserIdAndUrl(final Integer UserId, final String Url);
}