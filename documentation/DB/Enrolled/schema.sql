CREATE TABLE IF NOT EXISTS Enrolled (
    enroll_id INT AUTO_INCREMENT,
    PRIMARY KEY (enroll_id),
    final_grade INT,
    credits_earned INT,
    letter_grade CHAR(1),
    student_id INT,
    FOREIGN KEY (student_id)
        REFERENCES Student (student_id),
    section_id INT,
    FOREIGN KEY (section_id)
        REFERENCES Section (section_id)
);

CREATE OR REPLACE VIEW `EnrolledV` AS
    SELECT 
        e.*,
        room,
        daysOfWeek,
        start_time,
        end_time,
        sec.course_id,
        c.name AS class,
        classDescription,
        stud.first_name AS Student_first_name,
        stud.last_name AS Student_last_name,
        emp.employee_id,
        emp.first_name AS Staff_first_name,
        emp.last_name AS Staff_last_name
    FROM
        Enrolled e
            LEFT JOIN
        Section sec ON e.section_id = sec.section_id
            LEFT JOIN
        Staff emp ON sec.employee_id = emp.employee_id
            LEFT JOIN
        Course c ON sec.course_id = c.course_id
            LEFT JOIN
        Student stud ON e.student_id = stud.student_id;