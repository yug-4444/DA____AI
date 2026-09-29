CREATE TABLE massive_users(
    user_id INTEGER,
	user_name TEXT,
	salary INTEGER,
	user_address TEXT
);
INSERT INTO massive_users(user_id,user_name,salary,user_address)
    SELECT 
	     g,
		'User_'||g,
		(random()*1000000)::int,
		'address_'||g
	FROM generate_series(1,10000) AS g;--random ->[0,1)
	
SELECT*FROM massive_users;

EXPLAIN ANALYZE SELECT* FROM massive_users WHERE user_id=7777;
CREATE INDEX idx_id ON massive_users(user_id);
EXPLAIN ANALYZE SELECT* FROM massive_users ;
EXPLAIN ANALYZE SELECT* FROM massive_users WHERE user_id=7777;