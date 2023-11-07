package com.authenticator.db.service;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.authenticator.db.entity.Operation;
import com.authenticator.db.repository.OperationRepository;

@Service
public class OperationService {
    private final OperationRepository strategyOperationRepository;

    @Autowired
    public OperationService(final OperationRepository strategyOperationRepository) {
        this.strategyOperationRepository = strategyOperationRepository;
    }

    public Optional<Operation> getStrategyOperationByName(final String name) {
        return strategyOperationRepository.findByName(name);
    }
}