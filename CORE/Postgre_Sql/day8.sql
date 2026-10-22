CREATE TABLE sales_team(
    agent_id INTEGER CONSTRAINT pk_a_id PRIMARY KEY,
	agent_name TEXT CONSTRAINT nn_aname NOT NULL,
	region TEXT CONSTRAINT nn_region NOT NULL,
	revenue NUMERIC(12,2)
);
INSERT INTO sales_team VALUES 
(1, 'Rahul', 'North', 150000),
(2, 'Priya', 'North', 250000),
(3, 'Amit', 'South', 180000),
(4, 'Neha', 'South', 220000),
(5, 'Kabir', 'East', 110000);

SELECT agent_name,region FROM sales_team WHERE revenue >(SELECT AVG(revenue) FROM sales_team);
SELECT agent_name FROM sales_team WHERE revenue >=ALL(SELECT revenue FROM sales_team);

SELECT agent_name,region,revenue FROM sales_team as s1 WHERE s1.revenue >(SELECT AVG(s2.revenue) FROM sales_team s2 WHERE s1.region=s2.region);
SELECT agent_name,region,revenue,(SELECT AVG(s2.revenue)FROM sales_team s2 WHERE s1.region=s2.region)as avg_region FROM sales_team as s1 WHERE s1.revenue >(SELECT AVG(s2.revenue) FROM sales_team s2 WHERE s1.region=s2.region);

SELECT agent_name,region,revenue FROM (SELECT region,AVG(revenue)AS region_avg FROM sales_team GROUP BY region)AS sub_teams NATURAL JOIN sales_team WHERE revenue>region_avg;