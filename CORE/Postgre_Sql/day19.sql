CREATE TABLE transactions(
    tran_id INTEGER,
	status TEXT,
	amount NUMERIC(10,2)
);
INSERT INTO transactions 
     SELECT g,
	        (ARRAY['ACCEPT','FAILURE','PENDING'])[floor(random()*3+1)],
			(random()*10000)::int
		FROM generate_series(1,50000)as g;
CREATE INDEX idx_bt_amount ON transactions USING BTREE(amount);
CREATE INDEX idx_h_id ON  transactions USING HASH(tran_id);

EXPLAIN ANALYZE SELECT *FROM transactions WHERE tran_id=4500;
EXPLAIN ANALYZE SELECT *FROM transactions WHERE tran_id>3000;
EXPLAIN ANALYZE SELECT *FROM transactions WHERE amount>9000;