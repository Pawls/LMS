SELECT * FROM sectionV;

SELECT COUNT(*) AS `No. Course` FROM Course;

SELECT 
course_id,
class,
COUNT(*) AS `No. Sections` 
FROM sectionV
GROUP BY course_id;

SELECT * FROM sectionV
WHERE section_id = ??;

INSERT INTO Section (course_id, employee_id, room, daysOfWeek, start_time, end_time)
VALUES (course_id, EMPLOYEE_ID, ROOM, DAYSOFWEEK, START_TIME, END_TIME);

UPDATE Section
SET course_id = course_id, employee_id = EMPLOYEE_ID, room = ROOM, daysOfWeek = DAYSOFWEEK, start_time = START_TIME, end_time = END_TIME
WHERE section_id = ID;

DELETE FROM Section
WHERE section_id = ID;