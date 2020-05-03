#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "loginwindow.h"
#include <QModelIndex>
#include "editablesqlmodel.h"
#include <QInputDialog>
#include <QMessageBox>
#include <utility> 
AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::getLoginData(const QString& fname, QString email, QString id)
{
    username = std::move(email);
    user_id = std::move(id);
    ui->label_admFname->setText(fname);
    refreshTable(ui->tableView_students); // Set up Home tab
}

void AdminWindow::refreshTable(QTableView * tbl_ptr)
{
    LoginWindow conn;
    conn.connOpen();

    auto* model = new QSqlQueryModel;
    QSqlQuery * qry = new QSqlQuery(conn.mydb);
    if(tbl_ptr->objectName() == "tableView_students")
        qry->prepare("SELECT student_id,degree_id,date_admitted,first_name,last_name,address,city,state,zip_code,phone,email "
                     "FROM Student");
    qry->exec();
    model->setQuery(*qry);
    tbl_ptr->setModel(model);
    conn.connClose();
}

void AdminWindow::on_pushButton_Add_clicked()
{
    QString degree_id; QString date_admitted; QString first_name; QString last_name; QString address; QString city; QString state; QString zip_code; QString phone; QString email; QString password;
    degree_id = ui->lineEdit_degree_id->text();
    date_admitted = ui->lineEdit_date_admitted->text();
    first_name = ui->lineEdit_first_name->text();
    last_name = ui->lineEdit_last_name->text();
    address = ui->lineEdit_address->text();
    city = ui->lineEdit_city->text();
    state = ui->lineEdit_state->text();
    zip_code = ui->lineEdit_zip_code->text();
    phone = ui->lineEdit_phone->text();
    email = ui->lineEdit_email->text();

    bool ok;
    password = QInputDialog::getText(this, tr(""),
                                         tr("Please assign temporary password."), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !password.isEmpty())
    {
        LoginWindow conn;
        conn.connOpen();
        QSqlQuery * qry = new QSqlQuery(conn.mydb);
        qry->prepare("INSERT INTO Student(degree_id,date_admitted,first_name,last_name,address,city,state,zip_code,phone,email,password) "
                     "VALUES (:degree_id,:date_admitted,:first_name,:last_name,:address,:city,:state,:zip_code,:phone,:email,:password)");
        qry->bindValue(":degree_id",degree_id);
        qry->bindValue(":date_admitted",date_admitted);
        qry->bindValue(":first_name",first_name);
        qry->bindValue(":last_name",last_name);
        qry->bindValue(":address",address);
        qry->bindValue(":city",city);
        qry->bindValue(":state",state);
        qry->bindValue(":zip_code",zip_code);
        qry->bindValue(":phone",phone);
        qry->bindValue(":email",email);
        qry->bindValue(":password",password);
        if(qry->exec())
            QMessageBox::information(this,"","Student added successfully.");
        else
            QMessageBox::information(this,"","Add student failed.");
        refreshTable(ui->tableView_students);
        conn.connClose();
    }
    else
    {
        QMessageBox::information(this,"","Add student aborted.");
    }
}

void AdminWindow::on_tableView_students_activated(const QModelIndex &index) // Populates lineEdits with selected row data
{
    ui->label_id->setText(index.sibling(index.row(),0).data().toString());
    ui->lineEdit_degree_id->setText(index.sibling(index.row(),1).data().toString());
    ui->lineEdit_date_admitted->setText(index.sibling(index.row(),2).data().toString());
    ui->lineEdit_first_name->setText(index.sibling(index.row(),3).data().toString());
    ui->lineEdit_last_name->setText(index.sibling(index.row(),4).data().toString());
    ui->lineEdit_address->setText(index.sibling(index.row(),5).data().toString());
    ui->lineEdit_city->setText(index.sibling(index.row(),6).data().toString());
    ui->lineEdit_state->setText(index.sibling(index.row(),7).data().toString());
    ui->lineEdit_zip_code->setText(index.sibling(index.row(),8).data().toString());
    ui->lineEdit_phone->setText(index.sibling(index.row(),9).data().toString());
    ui->lineEdit_email->setText(index.sibling(index.row(),10).data().toString());
}

void AdminWindow::on_pushButton_Clear_clicked()
{
    ui->label_id->setText("");
    ui->lineEdit_degree_id->setText("");
    ui->lineEdit_date_admitted->setText("");
    ui->lineEdit_first_name->setText("");
    ui->lineEdit_last_name->setText("");
    ui->lineEdit_address->setText("");
    ui->lineEdit_city->setText("");
    ui->lineEdit_state->setText("");
    ui->lineEdit_zip_code->setText("");
    ui->lineEdit_phone->setText("");
    ui->lineEdit_email->setText("");
}

void AdminWindow::on_pushButton_Delete_clicked()
{
    QString student_id = ui->label_id->text();
    if(student_id != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"","Are you sure you want to delete student "+student_id+"?");

        if (reply == QMessageBox::Yes)
        {
            LoginWindow conn;
            conn.connOpen();
            QSqlQuery * qry = new QSqlQuery(conn.mydb);
            qry->prepare("DELETE FROM Student WHERE student_id=:id");
            qry->bindValue(":id",student_id);
            if(qry->exec())
                QMessageBox::information(this,"","Student delete successful.");
            else
                QMessageBox::information(this,"","Student delete failed.");
            conn.connClose();
            on_pushButton_Clear_clicked();
            refreshTable(ui->tableView_students);
        }
    }
    else
        QMessageBox::information(this,"","Cannot delete NULL student");

}

void AdminWindow::on_pushButton_Update_clicked()
{
    QString student_id; QString degree_id; QString date_admitted; QString first_name; QString last_name; QString address; QString city; QString state; QString zip_code; QString phone; QString email;
    student_id = ui->label_id->text();
    degree_id = ui->lineEdit_degree_id->text();
    date_admitted = ui->lineEdit_date_admitted->text();
    first_name = ui->lineEdit_first_name->text();
    last_name = ui->lineEdit_last_name->text();
    address = ui->lineEdit_address->text();
    city = ui->lineEdit_city->text();
    state = ui->lineEdit_state->text();
    zip_code = ui->lineEdit_zip_code->text();
    phone = ui->lineEdit_phone->text();
    email = ui->lineEdit_email->text();

    if(student_id != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"","Are you sure you want to update student "+student_id+"?");
        if (reply == QMessageBox::Yes)
        {
            LoginWindow conn;
            conn.connOpen();
            QSqlQuery * qry = new QSqlQuery(conn.mydb);
            qry->prepare("UPDATE Student SET "
                         "degree_id=:degree_id,"
                         "date_admitted=:date_admitted,"
                         "first_name=:first_name,"
                         "last_name=:last_name,"
                         "address=:address,"
                         "city=:city,"
                         "state=:state,"
                         "zip_code=:zip_code,"
                         "phone=:phone,"
                         "email=:email "
                         "WHERE student_id=:student_id");
            qry->bindValue(":student_id",student_id);
            qry->bindValue(":degree_id",degree_id);
            qry->bindValue(":date_admitted",date_admitted);
            qry->bindValue(":first_name",first_name);
            qry->bindValue(":last_name",last_name);
            qry->bindValue(":address",address);
            qry->bindValue(":city",city);
            qry->bindValue(":state",state);
            qry->bindValue(":zip_code",zip_code);
            qry->bindValue(":phone",phone);
            qry->bindValue(":email",email);
            if(qry->exec())
                QMessageBox::information(this,"","Student update successful.");
            else
                QMessageBox::information(this,"","Student update failed.");
            conn.connClose();
            refreshTable(ui->tableView_students);
        }
    }
    else
        QMessageBox::information(this,"","Student does not exist. Please use ADD Record.");
}
