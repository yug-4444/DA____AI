CREATE TABLE department(
    dept_id INTEGER PRIMARY KEY,
	dept_name TEXT,
	dept_location TEXT
);
CREATE TABLE employee(
    emp_id INTEGER PRIMARY KEY,
	emp_name TEXT,
	dept_id INTEGER,
	FOREIGN KEY(dept_id)REFERENCES department(dept_id)
);
INSERT INTO department VALUES (10, 'Engineering', 'Building A'),(20, 'Sales', 'Building B');
INSERT INTO employee VALUES (1, 'Rahul', 10),(2, 'Priya', 10),(3, 'Amit', 20),(4, 'Neha', 20);

CREATE VIEW legacy_employee_data AS
SELECT emp_id,emp_name,d.dept_id,dept_name,dept_location
FROM department as d INNER JOIN employee as e ON d.dept_id=e.dept_id;

SELECT * FROM legacy_employee_data;
INSERT INTO legacy_employee_data VALUES (5, 'Kabir', 30, 'HR', 'Building C');

CREATE MATERIALIZED VIEW legacy AS
SELECT emp_id,emp_name,d.dept_id,dept_name,dept_location
FROM department as d INNER JOIN employee as e ON d.dept_id=e.dept_id;
SELECT * FROM legacy;
INSERT INTO legacy VALUES (5, 'Kabir', 30, 'HR', 'Building C');

INSERT INTO employee VALUES (6, 'RaKEAH', 10);
SELECT * FROM legacy_employee_data;
SELECT * FROM legacy;-- It will not reflect the change until the materialized view is refreshed.
REFRESH MATERIALIZED VIEW legacy;