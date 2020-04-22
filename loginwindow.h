#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <mainwindow.h>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    bool verifyLogin(QString, QString);

signals:
    void loginAcquired(QString);

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::LoginWindow *ui;
    LoginWindow *MainWindow;
    QSqlDatabase mydb;
};
#endif // LOGINWINDOW_H
