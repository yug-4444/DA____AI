CREATE TABLE doctors(
    doc_id INTEGER CONSTRAINT pk_docid PRIMARY KEY,
	doc_name TEXT CONSTRAINT nn_docname NOT NULL,
	department TEXT NOT NULL
);
CREATE TABLE surgeries(
    surg_id INTEGER CONSTRAINT pk_sugid PRIMARY KEY,
	doc_id INTEGER,
	surg_cost NUMERIC(10,2),
	CONSTRAINT fk_doc_id FOREIGN KEY(doc_id) REFERENCES doctors(doc_id)
);
INSERT INTO doctors VALUES 
(1, 'Dr. House', 'Diagnostic'),
(2, 'Dr. Chase', 'Surgery'),
(3, 'Dr. Foreman', 'Diagnostic'),
(4, 'Dr. Cameron', 'Immunology');

INSERT INTO surgeries VALUES 
(101, 1, 5000), (102, 1, 8000),
(103, 2, 15000), (104, 2, 12000), (105, 2, 9000),
(106, 3, 4000);

WITH revenue as (SELECT doc_id,SUM(surg_cost) as total_revenue FROM surgeries GROUP BY doc_id)
     SELECT * FROM revenue WHERE total_revenue>10000;

WITH dep_stats as(SELECT department,SUM(surg_cost) as dep_revenue FROM (SELECT * FROM doctors d INNER JOIN surgeries s ON d.doc_id=s.doc_id) GROUP BY department),
     dep_avg as(SELECT AVG(dep_revenue)as avg_cost FROM dep_stats)
	 SELECT department FROM dep_stats,dep_avg WHERE dep_stats.dep_revenue>dep_avg.avg_cost;