SELECT * FROM Course;

SELECT COUNT(*) AS `No. Course` FROM Course;

SELECT * FROM Course
WHERE course_id = ??;

INSERT INTO Course (name, description, credit_hours)
VALUES (??, ??, ??);

UPDATE Course
SET name = ??, description = ??, credit_hours = ??
WHERE course_id = ??;

DELETE FROM Course
WHERE course_id = ??;