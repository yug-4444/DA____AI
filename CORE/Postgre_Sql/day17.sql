CREATE TABLE corp_employee(
     emp_id INTEGER,
	 department TEXT,
	 salary NUMERIC(10,2)
);
INSERT INTO corp_employee 
     SELECT g,
	        (ARRAY['IT','SALES','TECH'])[FLOOR(random()*3+1)],
			(random()*1000000)::int
	 FROM generate_series(1,10000)AS g;

CREATE INDEX idx_dep_sal ON corp_employee(department,salary);
EXPLAIN ANALYZE SELECT* FROM corp_employee;
EXPLAIN ANALYZE SELECT * FROM corp_employee WHERE department='IT'AND salary=10000;

EXPLAIN ANALYZE SELECT * FROM corp_employee WHERE department='IT';
EXPLAIN ANALYZE SELECT * FROM corp_employee WHERE salary=10000;
