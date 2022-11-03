#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->lineEdit_4->setPlaceholderText("Unesite vase ime");
    ui->lineEdit_3->setPlaceholderText("Unesite vas email");
    ui->lineEdit_2->setPlaceholderText("Unesite vasu sifru");
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    //povezivanje SQL baze
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("qt5register");

    if(database.open())
{
        QString ime,email,sifra;
        ime = ui->lineEdit_4->text();
        email = ui->lineEdit_3->text();
        sifra = ui->lineEdit_2->text();
        QSqlQuery qry;
        qry.prepare("INSERT INTO users (ime,email,sifra)"
                    "VALUES (:ime, :email, :sifra)");
        qry.bindValue(":ime", ime);
        qry.bindValue(":email", email);
        qry.bindValue(":sifra", sifra);

        if(qry.exec()){
            QMessageBox::information(this,"Ubacenu u bazu","Uspjesno");
        }
        else{
             QMessageBox::information(this,"Nije ubacen u bazu","Neuspjesno");
        }

}
   else{
         QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

}

}

