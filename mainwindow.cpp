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

void MainWindow::getLoginData(QString fname, QString email)
{
    username = email;
    ui->label_username->setText(fname);

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
    qry->prepare("SELECT section_id FROM Enrolled WHERE student_id=(SELECT student_id FROM Student WHERE email=:USER)");
    qry->bindValue(":USER", username);
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_enrollment->setModel(model);
    conn.connClose();
    //qDebug() << (model->rowCount());
}

// Unecessary, because I created a LoginWindow object
void MainWindow::getDatabase(QSqlDatabase db)
{
    mydb = db;
}
