#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
//#include <mainwindow.h>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
//#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        QString database_path = "/data/mydb.db";
        QString path = QDir::currentPath() + database_path;
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName(path);

        if(!mydb.open())
        {
            qDebug() << "Failed to open the database\n";
            return false;
        }
        else
        {
            qDebug() << "Connected...\n";
            return true;
        }
    }


public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginAcquiredStudent(QString, QString, QString); //slot MainWindow::getLoginData
    void loginAcquiredAdmin(QString, QString, QString); //slot AdminWindow::getLoginData
    //void databaseOpen(QSqlDatabase);

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::LoginWindow *ui;
    LoginWindow *MainWindow{};

};
#endif // LOGINWINDOW_H
