SELECT * FROM Degree;

SELECT * FROM Degree
WHERE degree_id = ??;

SELECT COUNT(*) AS `No. Degrees` FROM Degree;

INSERT INTO Degree (degreeName, degreeDescription)
VALUES (??, ??);

UPDATE Degree
SET degreeName = ??, degreeDescription = ??
WHERE degree_id = ??;

DELETE FROM Degree
WHERE degree_id = ??;