SELECT * FROM instructorView;

SELECT * FROM adminView;

SELECT * FROM instructorView
WHERE employee_id = ??;

SELECT * FROM adminView
WHERE employee_id = ??;

SELECT manager_id, Manager_last_name, Manager_first_name, COUNT(*) AS `No. Employees` 
FROM instructorView
GROUP BY manager_id, Manager_last_name, Manager_first_name;

INSERT INTO Staff (manager_id, role, salary, date_hired, first_name, last_name, address, city, state, zip_code, phone, email, password)
VALUES (??, ??, ??, ??, ??, ??, ??, ??, ??, ??, ??, ??, ??);

UPDATE Staff
SET manager_id = ??, role = ??, salary = ??, date_hired = ??, first_name = ??, last_name = ??, address = ??, city = ??, state = ??, zip_code = ??, phone = ??, email = ??, password = ??
WHERE employee_id = ??;

DELETE FROM Staff
WHERE employee_id = ??;