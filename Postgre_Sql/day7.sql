CREATE TABLE departments(
    dep_id INTEGER CONSTRAINT pk_d_id PRIMARY KEY,
	dep_name TEXT CONSTRAINT nn_dname NOT NULL
);

CREATE TABLE payroll(
    emp_id INTEGER CONSTRAINT pk_e_id PRIMARY KEY,
	emp_name TEXT CONSTRAINT nn_ename NOT NULL,
	dep_id INTEGER,
	salary NUMERIC(10,2) CONSTRAINT nn_sal NOT NULL,
	bonus NUMERIC(10,2),
	CONSTRAINT fk_d_id FOREIGN KEY(dep_id) REFERENCES departments(dep_id)
);
--insert data
INSERT INTO departments VALUES (1, 'Engineering'), (2, 'Sales'), (3, 'HR');

INSERT INTO payroll VALUES 
(101, 'Rahul', 1, 120000, 10000),
(102, 'Priya', 1, 90000, NULL),
(103, 'Amit', 1, 95000, 5000),
(104, 'Neha', 2, 60000, 20000),
(105, 'Kabir', 2, 55000, 15000),
(106, 'Sara', 3, 70000, NULL);

SELECT * FROM payroll;
SELECT COUNT(*),COUNT(bonus) as total_bouns,AVG(salary) as avg_sal FROM payroll;

SELECT dep_id,COUNT(*),SUM(salary) FROM payroll GROUP BY dep_id;
SELECT dep_name,MAX(salary) FROM (SELECT * FROM payroll p LEFT JOIN departments d ON p.dep_id=d.dep_id)GROUP BY dep_name;
SELECT dep_id,COUNT(*),SUM(salary) FROM payroll GROUP BY dep_id HAVING SUM(salary)>150000;
