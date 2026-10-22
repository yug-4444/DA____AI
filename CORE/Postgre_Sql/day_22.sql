CREATE TABLE monthly_sale(
     s_month TEXT,
	 s_product TEXT,
	 s_revenue INTEGER
);
INSERT INTO monthly_sale VALUES('Jan', 'Laptop', 5000), ('Jan', 'Phone', 3000),('Feb', 'Laptop', 6000), ('Feb', 'Phone', 2500),('Mar', 'Laptop', 4500), ('Mar', 'Phone', 3200);

SELECT s_month,
       SUM(CASE WHEN s_product='Laptop'THEN s_revenue END)AS laptop_revenue,
	   SUM(CASE WHEN s_product='Phone'THEN s_revenue END)AS phone_revenue
FROM monthly_sale GROUP BY s_month 
ORDER BY CASE
            WHEN s_month='Jan'THEN 1
			WHEN s_month='Feb'THEN 2
			WHEN s_month='March'THEN 3
			END;

CREATE TABLE user_orders(
    user_id INTEGER,
	order_status TEXT
);
INSERT INTO user_orders VALUES 
(1, 'PENDING'), (1, 'DELIVERED'), (1, 'DELIVERED'),
(2, 'PENDING'), (2, 'PENDING'), (2, 'SHIPPED'),
(3, 'DELIVERED');
SELECT user_id,
       SUM(CASE WHEN order_status='PENDING' THEN 1 ELSE 0 END)AS count_pending,
	   SUM(CASE WHEN order_status='DELIVERED' THEN 1 ELSE 0 END)AS count_delivered,
	   SUM(CASE WHEN order_status='SHIPPED' THEN 1 ELSE 0 END)AS count_shipped
FROM user_orders
GROUP BY user_id
ORDER BY user_id;

CREATE TABLE user_attribute(
    user_id INTEGER,
	attribute_key TEXT,
	attribute_value TEXT
);
INSERT INTO user_attribute VALUES (1, 'email', 'alice@gmail.com'),(1, 'phone', '555-0100'),(2, 'email', 'bob@yahoo.com'),(2, 'location', 'New York'),(3, 'phone', '555-0999');

SELECT user_id,
       MAX(CASE WHEN attribute_key='email'THEN attribute_value END) AS user_email,
	   MAX(CASE WHEN attribute_key='phone'THEN attribute_value END)AS user_phone,
	   MAX(CASE WHEN attribute_key='location'THEN attribute_value END) AS user_location
FROM user_attribute
GROUP BY user_id
ORDER BY user_id;