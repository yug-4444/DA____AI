--Challenge 1: The Conditional UPDATE The warehouse is doing a clearance sale. Write an UPDATE query that targets all products. Use a CASE statement in the SET clause so that:If current stock is 0, keep the price the same.If current stock is > 10, reduce the price by 10% (multiply by 0.9).
--Challenge 2: The Backend UPSERTA shipment arrives for 'Wireless Mouse' (Product ID 2) with 20 units. However, our Python backend doesn't know if Product 2 is already in the database.Write an INSERT statement for (2, 'Wireless Mouse', 20, 45.00).
--Challenge 3: The RETURNING Clause (Industry Standard)When you delete a row in the backend, you often need to show the user exactly what they just deleted.Write a query to DELETE the 'USB-C Cable' (product_id = 3), but append the keyword RETURNING *; to the very end of the statement. Notice how PostgreSQL outputs the deleted data.

CREATE TABLE prod(
    p_id INTEGER CONSTRAINT pk_proid PRIMARY KEY,
	p_name TEXT CONSTRAINT nn_proname NOT NULL,
	stock INTEGER CONSTRAINT ch_prostock CHECK(STOCK>=0),
	price NUMERIC(10,2) CONSTRAINT ch_proprice CHECK(price>0)
);
INSERT INTO prod VALUES 
(1, 'Mechanical Keyboard', 50, 120.00),
(2, 'Wireless Mouse', 5, 45.00),
(3, 'USB-C Cable', 0, 15.00);

UPDATE prod 
SET price=CASE
            WHEN stock>10 THEN price*0.9
			ELSE price
		   END
RETURNING *;

INSERT INTO prod VALUES (2,'Wireless Mouse',20,45) ON CONFLICT(p_id)DO UPDATE SET stock=prod.stock+EXCLUDED.stock
RETURNING *;

DELETE FROM prod WHERE p_name='USB-C Cable'
RETURNING *;
