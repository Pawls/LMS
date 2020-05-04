CREATE TABLE IF NOT EXISTS Student (
    student_id INT AUTO_INCREMENT NOT NULL,
    PRIMARY KEY (student_id),
    degree_id INT,
    FOREIGN KEY (degree_id)
        REFERENCES Degree (degree_id),
    date_admitted DATE DEFAULT '2000-01-01',
    first_name VARCHAR(255) NOT NULL,
    last_name VARCHAR(255) NOT NULL,
    address VARCHAR(255) DEFAULT 'TBD',
    city VARCHAR(255) DEFAULT 'TBD',
    state VARCHAR(255) DEFAULT 'TBD',
    zip_code INT DEFAULT 77024,
    phone VARCHAR(255) DEFAULT 'TBD',
    email VARCHAR(255) NOT NULL,
    password VARCHAR(25) DEFAULT 'asdf'
);

CREATE OR REPLACE VIEW `studentView` AS
    SELECT 
        *
    FROM
        Student
            NATURAL JOIN
        Degree;
        
CREATE OR REPLACE VIEW `admin_studentView` AS
    SELECT 
        degree_id,
        student_id,
        date_admitted,
        first_name,
        last_name,
        address,
        city,
        state,
        zip_code,
        phone,
        email,
        degreeName,
        degreeDescription
    FROM
        studentView;
        
CREATE OR REPLACE VIEW `instr_studentView` AS
    SELECT 
        degree_id,
        student_id,
        first_name,
        last_name,
        email
    FROM
        studentView;