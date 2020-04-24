#include "loginwindow.h"
#include "mainwindow.h"
#include "adminwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QString username;
    QApplication a(argc, argv);
    LoginWindow loginWindow;
    MainWindow mainWindow;
    AdminWindow adminWindow;

    QObject::connect(&loginWindow, SIGNAL(loginAcquiredStudent(QString,QString,QString)),
                     &mainWindow, SLOT(getLoginData(QString,QString,QString)));
    QObject::connect(&loginWindow, SIGNAL(loginAcquiredStudent(QString,QString,QString)),
                     &mainWindow, SLOT(show()));

    QObject::connect(&loginWindow, SIGNAL(loginAcquiredAdmin(QString,QString,QString)),
                     &adminWindow, SLOT(getLoginData(QString,QString,QString)));
    QObject::connect(&loginWindow, SIGNAL(loginAcquiredAdmin(QString,QString,QString)),
                     &adminWindow, SLOT(show()));
    //QObject::connect(&loginWindow, SIGNAL(databaseOpen(QSqlDatabase)),
     //                &mainWindow, SLOT(getDatabase(QSqlDatabase)));

    loginWindow.show();
    return a.exec();
}
