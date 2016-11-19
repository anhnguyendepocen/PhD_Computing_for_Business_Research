SHOW Databases;
USE sakila; SHOW TABLES;
DESC payment;

SELECT DISTINCT staff_id
FROM payment;

SELECT sum(a.amount),b.first_name
FROM payment a
LEFT JOIN staff b ON a.staff_id=b.staff_id
GROUP BY a.staff_id;

SELECT sum(a.amount) AS sales_leader, b.first_name
FROM payment a
LEFT JOIN staff b ON a.staff_id=b.staff_id
GROUP BY a.staff_id
ORDER BY sales_leader DESC LIMIT 1;

-- 'VIEW' creates a 'temporary table'
CREATE VIEW salesleader AS
SELECT sum(a.amount) AS sales_leader,b.first_name
FROM payment a
LEFT JOIN staff b ON a.staff_id=b.staff_id
GROUP BY a.staff_id
ORDER BY sales_leader DESC LIMIT 1;
SELECT * FROM salesleader;

-- Nested commands
SELECT * FROM film WHERE title='MASSACRE USUAL';
SELECT inventory_id FROM inventory WHERE film_id=563;
SELECT inventory_id, customer_id
FROM inventory
WHERE inventory_id IN
(SELECT inventory_id FROM inventory WHERE film_id=563);


-- 1a
SELECT COUNT(*) FROM rental;

-- 1b
SELECT rental_date FROM rental;
SELECT staff_id, COUNT(*) FROM rental WHERE rental_date LIKE '2005%' GROUP BY staff_id;

-- 1c
SELECT a.category_id, b.name, COUNT(a.film_id) AS number_of_films
FROM film_category a
LEFT JOIN category b ON a.category_id=b.category_id
GROUP BY a.category_id
ORDER BY number_of_films DESC LIMIT 10;

-- 1d
SELECT SUM(active)/COUNT(*) AS percent_active FROM customer;

-- 1e
SELECT CONCAT(20*FLOOR(total_amt/20), '-', 20*FLOOR(total_amt/20)+20) AS dRange, 
COUNT(*) AS '# of Customers' FROM (SELECT SUM(amount) AS 'total_amt' FROM payment GROUP BY customer_id) a
GROUP BY dRange ORDER BY total_amt;
-- http://stackoverflow.com/questions/6687534/group-by-range-in-mysql
-- SELECT COUNT(*), total_amt FROM 
-- (SELECT FLOOR(SUM(amount)/10) AS total_amt FROM payment P GROUP BY customer_id) AS T 
-- GROUP BY total_amt;


-- 2a
SELECT * FROM rental;
SELECT * FROM inventory;
SELECT a.film_id, a.inventory_id, SUM(DATE(b.rental_date) BETWEEN '2005-6-01' AND '2005-6-20') AS 'times_rented'
FROM inventory a
LEFT JOIN rental b ON a.inventory_id=b.inventory_id
GROUP BY a.inventory_id;

-- 2b
CREATE VIEW rental_record_6 AS
SELECT a.film_id, COUNT(DISTINCT a.inventory_id) AS total_inventory, 
SUM(DATE(b.rental_date) BETWEEN '2005-6-01' AND '2005-6-20')  AS times_rented
FROM inventory a
LEFT JOIN rental b ON a.inventory_id=b.inventory_id 
GROUP BY a.film_id;

SELECT * FROM rental_record_6;

-- 3
CREATE TABLE adult_train (
  `Age` INTEGER NOT NULL,
  `Work_Class` VARCHAR(50) NOT NULL DEFAULT '',
  `FNLWGT` INTEGER NOT NULL,
  `Education` VARCHAR(50) NOT NULL DEFAULT '',
  `Education_Num` INTEGER NOT NULL,
  `Marital_Status` VARCHAR(50) NOT NULL DEFAULT '',
  `Occupation` VARCHAR(50) NOT NULL DEFAULT '',
  `Relationship` VARCHAR(50) NOT NULL DEFAULT '',
  `Race` VARCHAR(50) NOT NULL DEFAULT '',
  `Sex` VARCHAR(50) NOT NULL DEFAULT '',
  `Capital_Gain` INTEGER NOT NULL DEFAULT '0',
  `Capital_Loss` INTEGER NOT NULL DEFAULT '0',
  `Hours_Per_Week` INTEGER NOT NULL DEFAULT '0',
  `Native_Country` VARCHAR(50) NOT NULL DEFAULT '',
  `Income` VARCHAR(50) NOT NULL DEFAULT '');

LOAD DATA LOCAL INFILE 'D:/Tools/SQL_Data/adult.data'
INTO TABLE adult_train
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n';

SELECT * FROM adult_train;
SELECT COUNT(*) FROM adult_train;

CREATE TABLE adult_test (
  `Age` INTEGER NOT NULL,
  `Work_Class` VARCHAR(50) NOT NULL DEFAULT '',
  `FNLWGT` INTEGER NOT NULL,
  `Education` VARCHAR(50) NOT NULL DEFAULT '',
  `Education_Num` INTEGER NOT NULL,
  `Marital_Status` VARCHAR(50) NOT NULL DEFAULT '',
  `Occupation` VARCHAR(50) NOT NULL DEFAULT '',
  `Relationship` VARCHAR(50) NOT NULL DEFAULT '',
  `Race` VARCHAR(50) NOT NULL DEFAULT '',
  `Sex` VARCHAR(50) NOT NULL DEFAULT '',
  `Capital_Gain` INTEGER NOT NULL DEFAULT '0',
  `Capital_Loss` INTEGER NOT NULL DEFAULT '0',
  `Hours_Per_Week` INTEGER NOT NULL DEFAULT '0',
  `Native_Country` VARCHAR(50) NOT NULL DEFAULT '',
  `Income` VARCHAR(50) NOT NULL DEFAULT '');

LOAD DATA LOCAL INFILE 'D:/Tools/SQL_Data/adult.test'
INTO TABLE adult_test
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n';

SELECT * FROM adult_test;
SELECT COUNT(*) FROM adult_test;

