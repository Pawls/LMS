CREATE TABLE IF NOT EXISTS Degree (
    degree_id INT AUTO_INCREMENT,
    PRIMARY KEY (degree_id),
    degreeName VARCHAR(255) NOT NULL,
    degreeDescription VARCHAR(255) DEFAULT 'TBD'
);
