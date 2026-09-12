CREATE TABLE coustomers(
   coustomer_id INTEGER CONSTRAINT pk_cid PRIMARY KEY,
   coustomer_name TEXT CONSTRAINT nn_cname NOT NULL,
   sign_up_date DATE DEFAULT CURRENT_DATE
);
CREATE TABLE products(
    product_id INTEGER CONSTRAINT pk_pid PRIMARY KEY,
	product_name TEXT CONSTRAINT nn_cname NOT NULL,
	price NUMERIC(10,2) CONSTRAINT ch_price CHECK(price>0) 
);
CREATE TABLE d5orders(
    order_id INTEGER CONSTRAINT pk_d5oid PRIMARY KEY,
	c_id INTEGER,
	p_id INTEGER,	
	CONSTRAINT fk_cid
	   FOREIGN KEY(c_id)
	   REFERENCES coustomers(coustomer_id)
	   ON DELETE CASCADE,
	CONSTRAINT fk_pid
	   FOREIGN KEY(p_id)
	   REFERENCES products(product_id)
	   ON DELETE RESTRICT
);

INSERT INTO coustomers VALUES
(1, 'Rahul'),
(2, 'Priya'),
(3, 'Amit'),
(4, 'Neha');

INSERT INTO products VALUES
(101, 'Mechanical Keyboard', 150.00),
(102, 'Wireless Mouse', 50.00),
(103, 'Monitor Stand', 80.00);

INSERT INTO d5orders VALUES
(5001, 1, 101),
(5002, 1, 102),
(5003, 2, 101),
(5004, 3, 102);

SELECT o.coustomer_name,product_name,price FROM (SELECT * FROM coustomers as c INNER JOIN d5orders as o ON c.coustomer_id=o.c_id)as o
      INNER JOIN products as p 
	    ON p.product_id=o.p_id;

SELECT product_name FROM products as p LEFT OUTER JOIN d5orders as o ON p.product_id=o.p_id
     WHERE order_id IS NULL;

SELECT coustomer_name FROM coustomers as c LEFT OUTER JOIN d5orders as o ON c.coustomer_id=o.c_id
     WHERE order_id IS NULL;

DELETE FROM products WHERE product_id = 103;
DELETE FROM products WHERE product_id = 101;