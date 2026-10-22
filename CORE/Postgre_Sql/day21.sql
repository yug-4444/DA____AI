CREATE TABLE raw_users(
    user_id INTEGER,
	salary NUMERIC(10,2)
);
INSERT INTO raw_users VALUES 
(1, 20000), (2, 22000), (3, 24000), (4, 25000), (5, 26000),
(6, 27000), (7, 28000), (8, 29000), (9, 30000), (10, 31000),
(11, 32000), (12, 33000), (13, 34000), (14, 35000), (15, 36000),
(16, 38000), (17, 40000), (18, 80000), (19, 150000), (20, 250000);

SELECT *,CASE
           WHEN salary<50000 THEN 'standard'
		   WHEN salary<100000 THEN 'senior'
		   ELSE 'elite' 
		   END AS salary_standrad
		 FROM raw_users;
SELECT user_id,salary,NTILE(4)OVER(ORDER BY salary)AS salary_quartile FROM raw_users;