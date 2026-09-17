CREATE TABLE legacy_employee_data(
    emp_id INTEGER,
	emp_name TEXT,
	dept_id INTEGER,
	dept_name TEXT,
	dept_location TEXT
);

INSERT INTO legacy_employee_data VALUES 
(1, 'Rahul', 10, 'Engineering', 'Building A'),
(2, 'Priya', 10, 'Engineering', 'Building A'),
(3, 'Amit', 20, 'Sales', 'Building B'),
(4, 'Neha', 20, 'Sales', 'Building B');

CREATE TABLE department(
    dept_id INTEGER PRIMARY KEY,
	dept_name TEXT,
	dept_location TEXT
);
CREATE TABLE employees(
    emp_id INTEGER PRIMARY KEY,
	emp_name TEXT,
	dept_id INTEGER,
	FOREIGN KEY (dept_id) REFERENCES department(dept_id)
);

WITH dep AS (SELECT DISTINCT dept_id,dept_name,dept_location FROM legacy_employee_data)
     INSERT INTO department
	 SELECT * FROM dep
	 ON CONFLICT(dept_id) DO NOTHING
	 RETURNING *;

WITH emp AS(SELECT DISTINCT emp_id,emp_name,dept_id FROM legacy_employee_data)
     INSERT INTO employees
	 SELECT * FROM emp
	 ON CONFLICT(emp_id) DO NOTHING 
	 RETURNING *;

SELECT * FROM employees;

SELECT * FROM department;