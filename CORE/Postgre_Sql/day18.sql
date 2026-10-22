CREATE TABLE coperate(
    emp_id INTEGER,
	department TEXT,
	salary NUMERIC(10,2)
);
INSERT INTO coperate 
     SELECT g,
	        'DEPT_'||(random()*1000)::int,
			(random()*1000000)::int
	 FROM generate_series(1,10000)AS g;
INSERT INTO coperate VALUES (999,'DEPT_48',100000);
--NOW IN GENRAL EACH DEPARTMENT WILL HAVE 10 ROW SO IN THIS CASE WHEN DEP AND SAL  IS OUR INDEX SCAN IT WILL FOLLOW OUR 
CREATE INDEX idx_d_s ON coperate(department,salary);
EXPLAIN ANALYZE SELECT* FROM coperate WHERE salary=10000;
EXPLAIN ANALYZE SELECT* FROM coperate WHERE department='DEPT_48';
EXPLAIN ANALYZE SELECT* FROM coperate WHERE department='DEPT_11';
EXPLAIN ANALYZE SELECT* FROM coperate WHERE department='DEPT_11'and salary=100000;