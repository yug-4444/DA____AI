CREATE TABLE d6students(
    s_id INTEGER CONSTRAINT pk_sid PRIMARY KEY,
	s_name TEXT CONSTRAINT nn_sname NOT NULL 
);
CREATE TABLE core_courses(
    c_id INTEGER CONSTRAINT pk_d6cid PRIMARY KEY,
	c_name TEXT CONSTRAINT nn_cname NOT NULL
);
CREATE TABLE enroll(
    s_id INTEGER,
	c_id INTEGER,
	PRIMARY KEY(s_id,c_id)
);
INSERT INTO d6students VALUES (1, 'Rahul'), (2, 'Priya'), (3, 'Amit');
INSERT INTO core_courses VALUES (101, 'Algorithms'), (102, 'Databases');

INSERT INTO enroll VALUES (1, 101), (1, 102);
INSERT INTO enroll VALUES (2, 101);
INSERT INTO enroll VALUES (3, 102);

SELECT s.s_name FROM d6students s WHERE EXISTS(SELECT * FROM enroll e WHERE s.s_id=e.s_id);

SELECT s.s_id FROM d6students s WHERE NOT EXISTS(SELECT * FROM core_courses c WHERE NOT EXISTS(SELECT * FROM enroll e WHERE s.s_id=e.s_id AND c.c_id=e.c_id));

SELECT s_id
FROM d6students
EXCEPT
SELECT s_id
FROM(
    SELECT s.s_id, c.c_id
    FROM d6students s
    CROSS JOIN core_courses c
    EXCEPT
    SELECT s_id, c_id
    FROM enroll
);