CREATE TABLE physical_tests(
    p_id INTEGER PRIMARY KEY,
	letter TEXT NOT NULL
);
INSERT INTO physical_tests VALUES (3, 'C');
INSERT INTO physical_tests VALUES (1, 'A');
INSERT INTO physical_tests VALUES (4, 'D');
INSERT INTO physical_tests VALUES (2, 'B');
--HEAP FILE
SELECT ctid,* FROM physical_tests;
UPDATE physical_tests SET letter='Z' WHERE p_id=1
returning ctid,*;
SELECT ctid,* FROM physical_tests;
CLUSTER physical_tests USING physical_tests_pkey;
SELECT ctid,* FROM physical_tests;