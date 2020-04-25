#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void getLoginData(QString, QString, QString);

    void on_pushButton_Add_clicked();

    void on_tableView_students_activated(const QModelIndex &index);

    void on_pushButton_Clear_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Update_clicked();

private:
    Ui::AdminWindow *ui;
    QString username;
    QString user_id;
    void refreshTable(QTableView *);
};

#endif // ADMINWINDOW_H
