CREATE TABLE subsriptions(
    user_id INTEGER CONSTRAINT pk_uerId PRIMARY KEY,
	plan_type TEXT CONSTRAINT nn_plan NOT NULL,
	months_active INTEGER CONSTRAINT nn_active NOT NULL,
	total_paid NUMERIC(10,2) CONSTRAINT nn_paid NOT NULL
);
INSERT INTO subsriptions VALUES(101, 'Basic', 11, 220.00),
(102, 'Pro', 24, 600.00);

INSERT INTO subsriptions as s VALUES (101, 'Basic', 1, 20.00) ON CONFLICT(user_id)
       DO UPDATE SET months_active=s.months_active+1,
	                 total_paid=s.total_paid+EXCLUDED.total_paid,
					 plan_type=CASE
					                WHEN s.months_active+1>=12 THEN 'Pro'--!!!!!!!!!!uses old active not newly updated as its not instantly updated
									ELSE s.plan_type
								 END
		RETURNING *;