CREATE TABLE IF NOT EXISTS Submission (
    submission_id INT AUTO_INCREMENT,
    PRIMARY KEY (submission_id),
    submission VARCHAR(8000),
    date_submitted DATETIME DEFAULT CURRENT_TIMESTAMP,
    points_earned INT,
    enroll_id INT,
    FOREIGN KEY (enroll_id)
        REFERENCES Enrolled (enroll_id),
    assn_id INT,
    FOREIGN KEY (assn_id)
        REFERENCES Assignment (assn_id)
);

CREATE OR REPLACE VIEW `submissionV` AS
    SELECT 
        e.enroll_id,
        sec.course_id,
        c.credit_hours,
        stud.student_id,
        stud.first_name AS Student_first_name,
        stud.last_name AS Student_last_name,
        assn.assn_id,
        assn.section_id,
        assn.name AS assignmentName,
        assn.description AS assignmentDescription,
        assn.date_due,
        assn.points_possible,
        sub.submission_id,
        sub.submission,
        sub.date_submitted,
        sub.points_earned
    FROM
        Assignment assn
            LEFT JOIN
        Submission sub ON assn.assn_id = sub.assn_id
            LEFT JOIN
        Enrolled e ON sub.enroll_id = e.enroll_id
            LEFT JOIN
        Section sec ON assn.section_id = sec.section_id
            LEFT JOIN
        Course c ON sec.course_id = c.course_id
            LEFT JOIN
        Student stud ON e.student_id = stud.student_id
    ORDER BY submission_id;