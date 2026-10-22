CREATE TABLE staff(
    emp_id INTEGER CONSTRAINT pk_eid PRIMARY KEY,
	emo_name TEXT CONSTRAINT nn_name NOT NULL,
	department TEXT CONSTRAINT nn_dep NOT NULL,
	salary NUMERIC(10,2),
	bonus NUMERIC(10,2)
);

INSERT INTO staff(emp_id,emo_name,department,salary,bonus)VALUES
(1,'A','IT',75000,5000),
(2,'B','HR',83000,NULL),
(3,'C','IT',200000,20000),
(4,'C','SALE',30000,30000),
(5,'D','SALE',30000,NULL);

SELECT emo_name,salary 
FROM staff;

SELECT *
FROM staff
WHERE salary BETWEEN 50000 AND 300000;

SELECT *
FROM staff
WHERE department IN('HR','SALE');

SELECT *
FROM staff
WHERE bonus IS NULL;

ALTER TABLE staff
RENAME COLUMN emo_name TO emp_name;

SELECT emp_name 
FROM staff;

SELECT DISTINCT emp_name 
FROM staff;