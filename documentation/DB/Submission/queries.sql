SELECT * FROM submissionV
ORDER BY submission_id;

SELECT * FROM submissionV
WHERE submission_id = ??;

SELECT * FROM submissionV
WHERE section_id = ?? AND enroll_id IS NOT NULL;

SELECT * FROM submissionV
WHERE section_id = ?? AND student_id = ??;

SELECT * FROM submissionV v
WHERE section_id = ?? AND NOT EXISTS (
    SELECT *
    FROM submissionV
    WHERE section_id = ?? and student_id = ?? and assn_id = v.assn_id
);

SELECT 
section_id,
type,
COUNT(submission_id) AS 'No. Submitted',
COUNT(*) - count(submission_id) AS 'No. Unsubmitted'
FROM submissionV
WHERE section_id = ??
GROUP BY type;


SELECT 
section_id,
type,
student_id,
COUNT(submission_id) AS 'No. Submitted'
FROM submissionV 
WHERE section_id = ?? AND student_id = ??
GROUP BY type;

SELECT * FROM submissionV
WHERE student_id = ??;


select 
v.section_id,
v.enroll_id,
    possible,
    format(sum(points_possible * (points_earned / 100)), 2) as earned,
    format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) as Grade,
    CASE
		WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 90 THEN 'A'
        WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 80 THEN 'B'
        WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 70 THEN 'C'
        WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 60 THEN 'D'
		ELSE 'F'
    END as letter
from submissionV v
LEFT JOIN (
	SELECT section_id, sum(points_possible) AS possible FROM assignmentV GROUP BY section_id
) o ON v.section_id = o.section_id
WHERE student_id = ??
GROUP BY section_id;

select 
v.section_id,
v.enroll_id,
    possible,
    format(sum(points_possible * (points_earned / 100)), 2) as earned,
    format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) as Grade,
    CASE
		WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 90 THEN 'A'
        WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 80 THEN 'B'
        WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 70 THEN 'C'
        WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 60 THEN 'D'
		ELSE 'F'
    END as letter
from submissionV v
LEFT JOIN (
	SELECT section_id, sum(points_possible) AS possible FROM assignmentV GROUP BY section_id
) o ON v.section_id = o.section_id
WHERE v.section_id = ?? AND student_id = ??;


UPDATE Enrolled e
INNER JOIN (
	SELECT 
		enroll_id,
        q.section_id,
		format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) as Grade,
		CASE
			WHEN format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) >= 90 THEN 'A'
			WHEN format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) >= 80 THEN 'B'
			WHEN format((sum(points_possible * (points_earned / 100)) / possible * 100), 2) >= 70 THEN 'C'
			WHEN format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) >= 60 THEN 'D'
			ELSE 'F'
		END as letter,
		CASE
			WHEN format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) >= 90 THEN credit_hours * 4
			WHEN format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) >= 80 THEN credit_hours * 3
			WHEN format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) >= 70 THEN credit_hours * 2
			WHEN format((sum(points_possible * (points_earned / 100))  / possible * 100), 2) >= 60 THEN credit_hours * 1
			ELSE 0
    END as cr_earned
	FROM submissionV q
    LEFT JOIN (
	SELECT section_id, sum(points_possible) AS possible FROM assignmentV GROUP BY section_id
    ) p ON q.section_id = p.section_id
    WHERE q.section_id = ID
	GROUP BY enroll_id
) o
ON e.enroll_id = o.enroll_id
SET e.letter_grade = letter, final_grade = Grade, credits_earned = cr_earned
WHERE e.section_id = ??;

INSERT INTO Submission (submission, enroll_id, assn_id)
VALUES (SUB, enroll_id, ASSN_ID);

UPDATE Submission
SET submission = SUB, enroll_id = enroll_id, assn_id = ASSN_ID
WHERE submission_id = ??;

UPDATE Submission
SET points_earned = EARNED
WHERE submission_id = ??;

DELETE FROM Submission
WHERE submission_id = ??;
