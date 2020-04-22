#include "loginwindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QString username;
    QApplication a(argc, argv);
    LoginWindow loginWindow;
    MainWindow mainWindow;

    QObject::connect(&loginWindow, SIGNAL(loginAcquired(QString)),
                     &mainWindow, SLOT(getLoginData(QString)));
    QObject::connect(&loginWindow, SIGNAL(loginAcquired(QString)),
                     &mainWindow, SLOT(show()));

    loginWindow.show();
    return a.exec();
}
