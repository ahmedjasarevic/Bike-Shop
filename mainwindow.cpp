#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_loginButton_clicked()
{
    Login LogInfo;
    LogInfo.setModal(true);
    LogInfo.exec();
}

void MainWindow::on_registerButton_clicked()
{
    Register RegisterInfo;
    RegisterInfo.setModal(true);
    RegisterInfo.exec();

}

