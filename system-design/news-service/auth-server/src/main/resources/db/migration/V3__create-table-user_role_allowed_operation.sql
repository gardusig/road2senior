CREATE TABLE tb_user_role_allowed_operation (
    id SERIAL PRIMARY KEY,
    user_role_id INT NOT NULL,
    operation_id INT NOT NULL,
    created_at TIMESTAMPTZ(6) NOT NULL,
    updated_at TIMESTAMPTZ(6) NOT NULL,
    CONSTRAINT fk_user_role FOREIGN KEY(user_role_id) REFERENCES tb_user_role(id),
    CONSTRAINT fk_operation FOREIGN KEY(operation_id) REFERENCES tb_operation(id)
);