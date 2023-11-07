package br.com.news.db.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import br.com.news.db.entity.ReadLater;
import br.com.news.db.repository.ReadLaterRepository;

@Service
public class ReadLaterService {
    private final ReadLaterRepository readLaterRepository;

    @Autowired
    public ReadLaterService(final ReadLaterRepository readLaterRepository) {
        this.readLaterRepository = readLaterRepository;
    }

    public void add(final ReadLater readLater) {
        if (this.readLaterRepository.findByUserIdAndUrl(readLater.getUserId(), readLater.getUrl()).isPresent()) {
            return;
        }
        this.readLaterRepository.save(readLater);
    }

    public void delete(final Integer userId, final String url) {
        this.readLaterRepository.deleteByUserIdAndUrl(userId, url);
    }

    public List<ReadLater> query(final Integer userId) throws Exception {
        return this.readLaterRepository.findAllByUserId(userId);
    }
}