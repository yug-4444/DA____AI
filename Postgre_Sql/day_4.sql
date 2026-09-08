CREATE TABLE region(
    region_id INTEGER CONSTRAINT pk_rid PRIMARY KEY,
	region_name TEXT CONSTRAINT nn_rname NOT NULL
);

CREATE TABLE warehouses(
    ware_id INTEGER CONSTRAINT pk_wid PRIMARY KEY,
	ware_name TEXT CONSTRAINT nn_wname NOT NULL,
	capacity INTEGER,
	region_id INTEGER,
	CONSTRAINT fk_rid 
	FOREIGN KEY(region_id)
	REFERENCES region(region_id)
);

INSERT INTO region VALUES 
(1,'North america'),
(2,'Europe');

INSERT INTO warehouses VALUES
(101,'NY',50000,1),
(102,'TX',100000,1),
(103,'London',810000,2);

SELECT * FROM region,warehouses;
SELECT * FROM region CROSS JOIN warehouses;
--SELECT * FROM region INNER JOIN warehouses; ->just runing this alone give us error syntax unmatch
SELECT * FROM region as r,warehouses as w WHERE r.region_id=w.region_id;
SELECT * FROM region as r INNER JOIN warehouses as w ON r.region_id=w.region_id;--don't remove same column present
SELECT * FROM region NATURAL JOIN warehouses;--remove same column present

SELECT r.region_name,w.ware_name,w.capacity,r.region_id FROM region as r INNER JOIN warehouses as w ON r.region_id=w.region_id;

SELECT r.region_name,w.ware_name FROM region as r INNER JOIN warehouses as w ON r.region_id=w.region_id and w.capacity>=60000;