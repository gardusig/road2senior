INSERT INTO tb_user_role (
        name,
        allowed_start_time,
        allowed_finish_time,
        created_at,
        updated_at
    )
VALUES (
        'ADMIN',
        '00:00:00.000000',
        '23:59:59.999999',
        NOW(),
        NOW()
    );