#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getLoginData(QString, QString, QString);

private:
    Ui::MainWindow *ui;
    QString username;
    QString user_id;
    void queryStudentHome();
};

#endif // MAINWINDOW_H
