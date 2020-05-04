CREATE TABLE IF NOT EXISTS Course (
    course_id INT AUTO_INCREMENT,
    PRIMARY KEY (course_id),
    name VARCHAR(255) NOT NULL,
    description VARCHAR(255) DEFAULT 'TBD',
    credit_hours INT DEFAULT 3
);