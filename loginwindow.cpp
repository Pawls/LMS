#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>

QString student_path = "/data/Student.csv";

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    QString database_path = "/data/mydb.db";
    QString path = QDir::currentPath() + database_path;
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(path);

    if(!mydb.open())
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
    if(verifyLogin(username, password))
    {
        QMessageBox::information(this, "Login", "Login Successful!");
        hide();
        //MainWindow = new LoginWindow(this);
        //MainWindow->show();
        emit loginAcquired(username);
    }
    else
        QMessageBox::information(this, "Login", "Username or password is incorrect.");

}

bool LoginWindow::verifyLogin(QString user, QString pass)
{
    QString path = QCoreApplication::applicationDirPath() + student_path;
    QMessageBox::information(this, "Debug",path);//QDir::currentPath()
    // Insert code to cross check login credentials against csv
    if(user == "Paul" && pass == "Davis")
        return true;
    else
        return false;
}

/*void loginAcquired(QString username)
{
    emit getLoginData(username);
}*/

