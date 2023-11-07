package com.authenticator.db.entity;

import java.sql.Time;
import java.sql.Timestamp;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.PrePersist;
import javax.persistence.PreUpdate;
import javax.persistence.Table;

import com.authenticator.util.TimeUtil;

@Entity
@Table(name = "tb_user_role")
public class UserRole {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @Column(name = "name", nullable = false)
    private String name;

    @Column(name = "allowed_start_time", nullable = false)
    private Time allowedStartTime;

    @Column(name = "allowed_finish_time", nullable = false)
    private Time allowedFinishTime;

    @Column(name = "created_at", nullable = false)
    private Timestamp createdAt;

    @Column(name = "updated_at", nullable = false)
    private Timestamp updatedAt;

    public Integer getId() {
        return this.id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Time getAllowedStartTime() {
        return this.allowedStartTime;
    }

    public void setAllowedStartTime(Time allowedStartTime) {
        this.allowedStartTime = allowedStartTime;
    }

    public Time getAllowedFinishTime() {
        return this.allowedFinishTime;
    }

    public void setAllowedFinishTime(Time allowedFinishTime) {
        this.allowedFinishTime = allowedFinishTime;
    }

    public Timestamp getCreatedAt() {
        return this.createdAt;
    }

    public void setCreatedAt(Timestamp createdAt) {
        this.createdAt = createdAt;
    }

    public Timestamp getUpdatedAt() {
        return this.updatedAt;
    }

    public void setUpdatedAt(Timestamp updatedAt) {
        this.updatedAt = updatedAt;
    }

    @PrePersist
    protected void onCreate() {
        this.createdAt = TimeUtil.getCurrentTimestamp();
        this.updatedAt = TimeUtil.getCurrentTimestamp();
    }

    @PreUpdate
    protected void onUpdate() {
        this.updatedAt = TimeUtil.getCurrentTimestamp();
    }
}