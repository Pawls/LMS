#include "datawindow.h"
#include "ui_datawindow.h"

DataWindow::DataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataWindow)
{
    ui->setupUi(this);
}

DataWindow::~DataWindow()
{
    delete ui;
}
