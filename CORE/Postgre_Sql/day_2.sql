CREATE TABLE users(
  user_id INTEGER CONSTRAINT pk_uid PRIMARY KEY,
  user_name TEXT CONSTRAINT nn_uname NOT NULL,
  user_email TEXT CONSTRAINT uq_email UNIQUE,
  account_balance NUMERIC(10,2) DEFAULT 0.0 CONSTRAINT ch_bal CHECK(account_balance>=0)
 );
 
 CREATE TABLE orders(
   order_no INTEGER CONSTRAINT pk_oid PRIMARY KEY,
   u_id INTEGER,
   order_total NUMERIC(10,2) CONSTRAINT ch_val CHECK(order_total>0),
   CONSTRAINT fk_uid
       FOREIGN KEY(u_id)
       REFERENCES users(user_id)
       ON DELETE RESTRICT
  );
  
  INSERT INTO users(user_id,user_name,user_email,account_balance)VALUES
  (1,'A','as.gamail.com',225222.22),
  (2,'B','ad.gmail.com',22222.55);
  
  INSERT INTO orders(order_no,u_id,order_total)VALUES
  (11,1,55);
  
  INSERT INTO orders(order_no,u_id,order_total)VALUES
  (12,2,5555);

  INSERT INTO orders(order_no,u_id,order_total)VALUES
  (13,1,5555);

  INSERT INTO orders(order_no,u_id,order_total)VALUES
  (14,20,5555);

  INSERT INTO users(user_id,user_name,user_email,account_balance)VALUES
  (5,'C','as.gamail.com',9999);