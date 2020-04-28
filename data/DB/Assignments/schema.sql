CREATE TABLE IF NOT EXISTS Assignment (
    assn_id INT AUTO_INCREMENT,
    PRIMARY KEY (assn_id),
    section_id INT,
    FOREIGN KEY (section_id)
        REFERENCES Section (section_id),
    points_possible INT,
    name VARCHAR(50) NOT NULL DEFAULT 'TBD',
    description VARCHAR(255) DEFAULT 'TBD',
    date_due DATE
);

CREATE OR REPLACE VIEW `assignmentV` AS
    SELECT 
        assn_id,
        assn.name AS assignmentName,
        assn.description AS assignmentDescription,
        date_due,
        points_possible,
        type,
        sec.*,
        c.name AS class,
        classDescription,
        first_name,
        last_name
    FROM
        Assignment assn
            LEFT JOIN
        Section sec ON assn.section_id = sec.section_id
            LEFT JOIN
        Course c ON sec.course_id = c.course_id
            LEFT JOIN
        Staff emp ON sec.employee_id = emp.employee_id;