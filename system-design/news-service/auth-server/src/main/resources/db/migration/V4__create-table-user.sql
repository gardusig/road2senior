CREATE TABLE tb_user (
    id SERIAL PRIMARY KEY,
    name VARCHAR(128) NOT NULL,
    email VARCHAR(256) NOT NULL UNIQUE,
    password VARCHAR(256),
    user_role_id INT NOT NULL,
    enabled BOOLEAN NOT NULL,
    consecutive_wrong_attempts INT NOT NULL,
    password_last_updated_at TIMESTAMPTZ(6),
    created_at TIMESTAMPTZ(6) NOT NULL,
    updated_at TIMESTAMPTZ(6) NOT NULL,
    CONSTRAINT fk_user_role FOREIGN KEY(user_role_id) REFERENCES tb_user_role(id)
);