SELECT * FROM EnrolledV;

SELECT * FROM EnrolledV
WHERE enroll_id = ??;

SELECT 
section_id,
class,
classDescription,
employee_id,
COUNT(*) AS `No. Student` 
FROM EnrolledV
GROUP BY section_id;

SELECT 
section_id,
class,
classDescription,
employee_id,
COUNT(*) AS `No. Student` 
FROM EnrolledV
WHERE section_id = ??
GROUP BY section_id;

INSERT INTO Enrolled (student_id, section_id)
VALUES (STUDENT_ID, SECTION_ID);

UPDATE Enrolled
SET final_grade = FINAL_GRADE, credits_earned = CREDITS_EARNED, letter_grade = LETTER_GRADE
WHERE enroll_id = ??;

DELETE FROM Enrolled
WHERE enroll_id = ID;