CREATE TABLE tb_read_later (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL,
    source_id VARCHAR(64),
    source_name VARCHAR(64) NOT NULL,
    author VARCHAR(64) NOT NULL,
    title VARCHAR(128) NOT NULL,
    description VARCHAR(512) NOT NULL,
    url VARCHAR(256) NOT NULL,
    url_to_image VARCHAR(256) NOT NULL,
    published_at VARCHAR(32) NOT NULL,
    content VARCHAR(512) NOT NULL,
    created_at TIMESTAMPTZ(6) NOT NULL,
    updated_at TIMESTAMPTZ(6) NOT NULL
);