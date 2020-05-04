SELECT * FROM assignmentV;

SELECT * FROM assignmentV
WHERE assn_id = ??;

SELECT * FROM assignmentV
WHERE section_id = ??;

SELECT 
section_id,
class,
classDescription,
employee_id,
COUNT(*) AS `No. Assignment` 
FROM assignmentV
GROUP BY section_id;

INSERT INTO Assignment (section_id, name, description, date_due)
VALUES (??, ??, ??, ??, ??);

UPDATE Assignment
SET section_id = ??, name = ??, description = ??, date_due = ??
WHERE assn_id = ??;

DELETE FROM Assignment
WHERE assn_id = ??;
