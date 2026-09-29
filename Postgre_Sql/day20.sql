CREATE TABLE sales_facts(
    sales_id INTEGER PRIMARY KEY,
	region TEXT,
	product_cataegory TEXT,
	revenue NUMERIC(10,2)
);
INSERT INTO sales_facts VALUES
    (1, 'North', 'Laptop', 1500),(2, 'North', 'Laptop', 1500),(3, 'North', 'Phone', 800),(4, 'South', 'Laptop', 1200),(5, 'South', 'Phone', 700),(6, 'South', 'Phone', 700);

SELECT region,product_cataegory,SUM(revenue) FROM sales_facts GROUP BY region,product_cataegory ORDER BY region;

SELECT region,product_cataegory,SUM(revenue) FROM sales_facts GROUP BY ROLLUP(region,product_cataegory);

SELECT region,product_cataegory,SUM(revenue)FROM sales_facts GROUP BY region,product_cataegory
      UNION ALL
	  SELECT region,NULL,SUM(revenue) FROM sales_facts GROUP BY region
	  UNION ALL
	  SELECT NULL,NULL,SUM(revenue) FROM sales_facts;

SELECT region,product_cataegory,SUM(revenue) FROM sales_facts GROUP BY CUBE(region,product_cataegory);

SELECT region,product_cataegory,SUM(revenue)FROM sales_facts GROUP BY region,product_cataegory
      UNION ALL
	  SELECT region,NULL,SUM(revenue) FROM sales_facts GROUP BY region
	  UNION ALL
	  SELECT NULL,product_cataegory ,SUM(revenue) FROM sales_facts GROUP BY product_cataegory
	  UNION ALL
	  SELECT NULL,NULL,SUM(revenue) FROM sales_facts;
