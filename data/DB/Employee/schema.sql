
CREATE TABLE IF NOT EXISTS Staff (
    employee_id INT AUTO_INCREMENT,
    PRIMARY KEY (employee_id),
    manager_id INT,
    FOREIGN KEY (manager_id)
        REFERENCES Staff (employee_id),
    role ENUM('Admin', 'Instructor') DEFAULT 'Instructor',
    salary INT NOT NULL DEFAULT 50000,
    date_hired DATE DEFAULT '2000-01-01',
    first_name VARCHAR(255) NOT NULL,
    last_name VARCHAR(255) NOT NULL,
    address VARCHAR(255) NOT NULL DEFAULT 'TBD',
    city VARCHAR(255) NOT NULL DEFAULT 'TBD',
    state VARCHAR(255) NOT NULL DEFAULT 'TBD',
    zip_code INT NOT NULL DEFAULT 77024,
    phone VARCHAR(25) NOT NULL DEFAULT 'TBD',
    email VARCHAR(255) NOT NULL,
    password VARCHAR(25) NOT NULL DEFAULT 'asdf'
);

CREATE OR REPLACE VIEW `employeeView` AS
    SELECT 
        e.*,
        m.first_name AS Manager_first_name,
        m.last_name AS Manager_last_name
    FROM
        Staff e
            LEFT JOIN
        Staff m ON e.manager_id = m.employee_id;

CREATE OR REPLACE VIEW `instructorView` AS
    SELECT 
        *
    FROM
        employeeView
    WHERE
        role = 'Instructor';

CREATE OR REPLACE VIEW `adminView` AS
    SELECT 
        *
    FROM
        Staff
    WHERE role = 'Admin';