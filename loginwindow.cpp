#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

QString student_path = "/data/Student.csv";

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    if(!connOpen())
        ui->label_status->setText("Failed to open the database");
    else
        ui->label_status->setText("Connected...");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString fname;
    QString user_id;

    if(!connOpen())
    {
        qDebug() << "Failed to open the database\n";
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT * FROM Student WHERE email='"+username+"' AND password='"+password+"'");
    qry.exec();
    int numberOfRows = 0;
    if(qry.last())
    {
        numberOfRows =  qry.at() + 1;
        qry.first();
        qry.previous();
    }
    if(numberOfRows > 0) // If Student Login
    {
        if(numberOfRows==1)
        {
            ui->label_status->setText("Username and password is correct");
            QSqlQuery qry("SELECT first_name FROM Student WHERE email='"+username+"'");
            while(qry.next())
            {
                fname = qry.value(0).toString();
            }
            QSqlQuery qry2("SELECT student_id FROM Student WHERE email='"+username+"'");
            while(qry2.next())
            {
                user_id = qry2.value(0).toString();
            }
            connClose();
            hide();
            emit loginAcquiredStudent(fname, username, user_id);
        }
        if(numberOfRows>1)
            ui->label_status->setText("Duplicate username and password");
        if(numberOfRows<1)
            ui->label_status->setText("Username and password is not correct");
    }
    else
    {
        qry.prepare("SELECT * FROM Staff WHERE email='"+username+"' AND password='"+password+"'");
        qry.exec();
        int numberOfRows = 0;
        if(qry.last())
        {
            numberOfRows =  qry.at() + 1;
            qry.first();
            qry.previous();
        }
        if(numberOfRows > 0) // If Admin Login
        {
            if(numberOfRows==1)
            {
                ui->label_status->setText("Username and password is correct");
                QSqlQuery qry("SELECT first_name FROM Staff WHERE email='"+username+"'");
                while(qry.next())
                {
                    fname = qry.value(0).toString();
                }
                QSqlQuery qry2("SELECT employee_id FROM Staff WHERE email='"+username+"'");
                while(qry2.next())
                {
                    user_id = qry2.value(0).toString();
                }
                connClose();
                hide();
                emit loginAcquiredAdmin(fname, username, user_id);
            }
            else if(numberOfRows>1)
                ui->label_status->setText("Duplicate username and password");
        }
        else ui->label_status->setText("Username and password is not correct");
    }
}
















