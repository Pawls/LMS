CREATE TABLE IF NOT EXISTS Section (
    section_id INT AUTO_INCREMENT,
    PRIMARY KEY (section_id),
    course_id INT,
    FOREIGN KEY (course_id)
        REFERENCES Course (course_id),
    employee_id INT,
    FOREIGN KEY (employee_id)
        REFERENCES Staff (employee_id),
    room VARCHAR(255) DEFAULT 'TBD',
    daysOfWeek VARCHAR(255) NOT NULL,
    start_time VARCHAR(255) DEFAULT 'TBD',
    end_time VARCHAR(255) DEFAULT 'TBD'
);

CREATE OR REPLACE VIEW `sectionV` AS
    SELECT 
        sec.section_id,
        room,
        daysOfWeek,
        start_time,
        end_time,
        c.course_id,
        c.name AS class,
        classDescription,
        credit_hours,
        emp.employee_id,
        first_name,
        last_name
    FROM
        Section sec
            LEFT JOIN
        Course c ON sec.course_id = c.course_id
            LEFT JOIN
        Staff emp ON sec.employee_id = emp.employee_id;