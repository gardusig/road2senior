package com.authenticator.db.repository;

import com.authenticator.db.entity.Operation;

import java.util.Optional;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface OperationRepository extends CrudRepository<Operation, Integer> {
    Optional<Operation> findByName(final String name);
}