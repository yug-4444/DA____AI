INSERT INTO departments(dep_id,dep_name) VALUES
(1,'MATHS'),
(2,'ENGLISH');

INSERT INTO students(stu_id,first_name,dep_id) VALUES
(1,'A',201),
(2,'B',NULL),
(3,'C',222);

ALTER TABLE students
ADD COLUMN dep_name TEXT;

SHOW timezone;

SELECT * FROM students;

UPDATE students 
SET dep_id=202
WHERE stu_id=2;

UPDATE students
SET middle_name='Z';

SELECT * FROM students;

SELECT "stu_id","first_name","dep_id" FROM students;