CREATE TABLE tb_password_reset_token (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL UNIQUE,
    token VARCHAR(512) NOT NULL UNIQUE,
    created_at TIMESTAMPTZ(6) NOT NULL,
    updated_at TIMESTAMPTZ(6) NOT NULL,
    CONSTRAINT fk_user FOREIGN KEY(user_id) REFERENCES tb_user(id)
);