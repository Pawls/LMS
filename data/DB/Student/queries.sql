SELECT * FROM studentView;

SELECT * FROM studentView
WHERE student_id = ??;

SELECT * FROM admin_studentView;

SELECT * FROM instr_studentView;

SELECT COUNT(*) AS `No. Students` FROM Student;

SELECT degree_id, degreeName, COUNT(*) AS `No. Students` 
FROM Student
NATURAL JOIN Degree
GROUP BY degree_id, degreeName;

INSERT INTO Student (degree_id, date_admitted, first_name, last_name, address, city, state, zip_code, phone, email, password)
VALUES (??, ??, ??, ??, ??, ??, ??, ??, ??, ??, ??);

SET degree_id = ??, date_admitted = ??, first_name = ??, last_name = ??, address = ??, city = ??, state = ??, zip_code = ??, phone = ??, email = ??, password = ??
WHERE student_id = ??;

DELETE FROM Student
WHERE student_id = ??;
