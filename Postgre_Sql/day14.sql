CREATE TABLE staff_salary(
    emp_id INTEGER PRIMARY KEY,
	emp_name TEXT NOT NULL,
	department TEXT NOT NULL,
	salary NUMERIC(10,2) NOT NULL
);
INSERT INTO staff_salary VALUES
    (1, 'Rahul', 'IT', 120000),(2, 'Priya', 'IT', 120000),(3, 'Amit', 'IT', 95000),(4, 'Neha', 'Sales', 150000),(5, 'Kabir', 'Sales', 110000),(6, 'Sara', 'Sales', 110000);

SELECT emp_name,salary,ROW_NUMBER()OVER(ORDER BY salary DESC,emp_id ASC)AS R_row_number,RANK()OVER(ORDER BY salary DESC)AS R_rank,DENSE_RANK()OVER(ORDER BY salary DESC)AS R_dense_rank FROM staff_salary;
SELECT * FROM staff_salary;

SELECT emp_name,salary,DENSE_RANK()OVER(PARTITION BY department ORDER BY salary DESC)AS R_dense_rank FROM staff_salary;

SELECT emp_name,department,salary,SUM(salary)OVER(PARTITION BY department ORDER BY emp_id ASC ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)AS running_cost FROM staff_salary;

WITH rank_table as(SELECT emp_id,emp_name,department,salary,DENSE_RANK()OVER(PARTITION BY department ORDER BY salary DESC)AS R_dense_rank FROM staff_salary)
SELECT * FROM rank_table WHERE R_dense_rank<=2;