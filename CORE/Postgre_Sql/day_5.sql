CREATE TABLE d5departments(
     dep_id INTEGER CONSTRAINT pk_depid PRIMARY KEY,
	 dep_name TEXT CONSTRAINT nn_dep_name NOT NULL 
);

CREATE TABLE d5employee(
    emp_id INTEGER CONSTRAINT pk_empid PRIMARY KEY,
	emp_name TEXT CONSTRAINT nn_ename NOT NULL,
	dep_id INTEGER--NOT A FK INTENTIONALLY AS TO USE FOR BASICS 
);
INSERT INTO d5departments VALUES
(1, 'Engineering'),
(2, 'Sales'),
(3, 'Marketing');

INSERT INTO d5employee VALUES
(101, 'Rahul', 1),
(102, 'Priya', 2),
(103, 'Amit', 1),
(104, 'Kabir', NULL);

SELECT * FROM d5departments AS d LEFT OUTER JOIN d5employee AS e ON d.dep_id=e.dep_id;

SELECT * FROM (d5departments AS d LEFT OUTER JOIN d5employee AS e ON d.dep_id=e.dep_id)
WHERE e.emp_id IS NULL;

SELECT dep_id FROM (SELECT dep_id FROM d5departments) EXCEPT (SELECT dep_id FROM d5employee);