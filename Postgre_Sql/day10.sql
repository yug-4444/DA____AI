CREATE TABLE customers(
    c_id INTEGER PRIMARY KEY,
	first_name TEXT,
	last_name TEXT,
	email TEXT
);
INSERT INTO customers VALUES 
(1, ' rahul ', 'sharma', 'Rahul.S@Company.com'),
(2, 'priya', NULL, 'priya_99@gmail.com'),
(3, 'amit', 'patel', 'amit.patel@100%secure.net'),
(4, 'neha', 'singh', 'neha@company.com');

--Challenge 1: The String Cleaner (TRIM, UPPER, LOWER)Notice Rahul's first name has leading and trailing spaces. Write a query to return all customers' first_name perfectly cleaned: removing all spaces and forcing the first letter to be uppercase and the rest lowercase.
--Challenge 2: The Safe Concatenation Write a query to create a full_name column by joining first_name and last_name with a space in between. Ensure Priya's name does not result in a NULL output.
--Challenge 3: The Wildcard Search Write a query to find the emails of customers who have a literal underscore (_) anywhere in their email address.
--Challenge 4: The Substring ExtractionWrite a query to extract only the domain name from the emails (everything after the @ symbol).


UPDATE customers SET first_name=UPPER(SUBSTRING(TRIM(first_name) FROM 1 FOR 1))||LOWER(SUBSTRING(TRIM(first_name),2))
RETURNING *;
UPDATE customers SET last_name=INITCAP(last_name)
RETURNING *;
UPDATE customers SET last_name=UPPER(SUBSTRING(TRIM(last_name) FROM 1 FOR 1))||LOWER(SUBSTRING(TRIM(last_name),2))
RETURNING *;--FASTER IN EXECTUTION COMPARED TO INITCAP
UPDATE customers SET last_name=UPPER(SUBSTRING(TRIM(last_name) FROM 1 FOR 1))||LOWER(SUBSTRING(TRIM(last_name),2)),
       first_name=UPPER(SUBSTRING(TRIM(first_name) FROM 1 FOR 1))||LOWER(SUBSTRING(TRIM(first_name),2))
       RETURNING *;

SELECT
first_name || COALESCE(' ' || last_name,'')
AS FULLname
FROM customers;
--if want to add a permanent column
ALTER TABLE customers ADD COLUMN full_name TEXT;
UPDATE customers SET full_name=first_name||COALESCE(' '||last_name,'')
RETURNING full_name;

SELECT*FROM customers;
SELECT c_id,email FROM customers WHERE email LIKE '%/_%'ESCAPE'/';

SELECT SPLIT_PART(email,'@',2) FROM customers;
SELECT SUBSTRING(email,POSITION('@'IN email)+1)FROM customers;