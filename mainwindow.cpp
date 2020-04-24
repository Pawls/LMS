#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include <QtSql>
//#include <QSqlRelationalTableModel>
#include <QModelIndex>

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
    queryStudentHome(); // Set up Home tab
}

void MainWindow::queryStudentHome() // Fill the homepage table for students
{
    LoginWindow conn;
    if(!conn.connOpen())
        ui->label_status->setText("Failed to open the database");
    else
        ui->label_status->setText("Connected...");

    // Fill Home table view===============================================================
    QSqlQueryModel* model = new QSqlQueryModel;
    //ui->tableView_enrollment->setModel(model);
    //ui->tableView_enrollment->show();
    ui->tableView_enrollment->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery * qry = new QSqlQuery(conn.mydb);
    qry->prepare("SELECT Enrolled.section_id,Course.name AS 'class',Staff.last_name AS Instructor,credit_hrs,"
                 "CASE "
                     "WHEN (((sum(points_earned)*1.00)/sum(points_possible))*100) >= 90 THEN 'A' "
                     "WHEN (((sum(points_earned)*1.00)/sum(points_possible))*100) >= 80 THEN 'B' "
                     "WHEN (((sum(points_earned)*1.00)/sum(points_possible))*100) >= 70 THEN 'C' "
                     "WHEN (((sum(points_earned)*1.00)/sum(points_possible))*100) >= 60 THEN 'D' "
                     "ELSE 'F' "
                 "END AS letter_grade "
                 "FROM Enrolled "
                 "JOIN Section ON Enrolled.section_id=Section.section_id "
                 "JOIN Course ON Section.course_id=Course.course_id "
                 "JOIN Staff ON Staff.staff_id=Section.instructor_id "
                 "LEFT JOIN Submission ON Enrolled.enroll_id=Submission.enroll_id "
                 "JOIN Assignment ON Enrolled.section_id = Assignment.section_id "
                 "WHERE student_id = :id "
                 "GROUP BY Enrolled.section_id");
    qry->bindValue(":id", user_id);
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_enrollment->setModel(model);
    //=====================================================================================
    // Fill Assignment table view===============================================================
    QSqlQueryModel* model_assn = new QSqlQueryModel;
    //ui->tableView_assignments->setModel(model_assn);
    //ui->tableView_assignments->show();
    ui->tableView_assignments->setEditTriggers(QAbstractItemView::NoEditTriggers);

    qry->prepare("SELECT "
                 "Enrolled.section_id,"
                 "Assignment.name as assignmentName,"
                 "Assignment.description as assignmentDescription,"
                 "Assignment.date_due,"
                 "Assignment.points_possible,"
                 "Submission.points_earned,"
                 "Submission.submission "
                 "FROM Submission "
                 "JOIN Enrolled ON Submission.enroll_id=Enrolled.enroll_id "
                 "JOIN Assignment ON Submission.assn_id = Assignment.assn_id "
                 "WHERE Enrolled.student_id = :id "
                 "ORDER BY Assignment.section_id");
    qry->bindValue(":id", user_id);
    qry->exec();
    model_assn->setQuery(*qry);
    ui->tableView_assignments->setModel(model_assn);
    //=====================================================================================

    conn.connClose();

    //Get tableView data for GPA here
    QModelIndex index;
    int total_hrs = 0;
    float earned_pts = 0;
    int current_hrs;
    QString grade;
    for (int row=0; row < model->rowCount(); row++)
    {
        index = model->index(row, 3);
        current_hrs = model->data(index).toInt();
        index = model->index(row, 4);
        grade = model->data(index).toString();

        if(grade == 'A')
            earned_pts += 4 * current_hrs;
        else if(grade == 'B')
            earned_pts += 3 * current_hrs;
        else if(grade == 'C')
            earned_pts += 2 * current_hrs;
        else if(grade == 'D')
            earned_pts += 1 * current_hrs;

        total_hrs += current_hrs;
    }

    ui->label_gpa->setText(QString::number(earned_pts/total_hrs,'f',2));
}













