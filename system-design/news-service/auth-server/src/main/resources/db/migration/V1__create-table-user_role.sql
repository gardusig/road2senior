CREATE TABLE tb_user_role (
    id SERIAL PRIMARY KEY,
    name VARCHAR(64) NOT NULL UNIQUE,
    allowed_start_time TIMETZ(6) NOT NULL,
    allowed_finish_time TIMETZ(6) NOT NULL,
    created_at TIMESTAMPTZ(6) NOT NULL,
    updated_at TIMESTAMPTZ(6) NOT NULL
);