#include "mainwindow.h"
#include "loginwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlRelationalTableModel>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getLoginData(QString fname, QString email, QString id)
{
    username = email;
    user_id = id;
    ui->label_username->setText(fname);

    queryStudentHome();
    //qDebug() << (model->rowCount());
}

// Unecessary, because I created a LoginWindow object
void MainWindow::getDatabase(QSqlDatabase db)
{
    mydb = db;
}

void MainWindow::queryStudentHome() // Fill the homepage table for students
{
    LoginWindow conn;
    if(!conn.connOpen())
        ui->label_status->setText("Failed to open the database");
    else
        ui->label_status->setText("Connected...");

    QSqlQueryModel* model = new QSqlQueryModel;
    ui->tableView_enrollment->setModel(model);
    ui->tableView_enrollment->show();
    ui->tableView_enrollment->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery * qry = new QSqlQuery(conn.mydb);
    qry->prepare("SELECT Enrolled.section_id,Course.name AS 'class',Staff.last_name AS Instructor,"
                 "((sum(points_earned)*1.00)/sum(points_possible))*100 as Grade "//"printf('%.2f%',((sum(points_earned)*1.00)/sum(points_possible))*100) as Grade"
                 "FROM Enrolled "
                 "JOIN Section ON Enrolled.section_id=Section.section_id "
                 "JOIN Course ON Section.course_id=Course.course_id "
                 "JOIN Staff ON Staff.staff_id=Section.instructor_id "
                 "JOIN Submission ON Enrolled.enroll_id=Submission.enroll_id "
                 "JOIN Assignment ON Enrolled.section_id = Assignment.section_id "
                 "WHERE student_id = :id "
                 "GROUP BY Enrolled.section_id");
    qry->bindValue(":id", user_id);
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_enrollment->setModel(model);
    conn.connClose();
}
