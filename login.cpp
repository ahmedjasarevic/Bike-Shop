#include "login.h"
#include "ui_login.h"
#include "dashboard.h"
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setPlaceholderText("Unesite vasu sifru");
     ui->lineEdit_3->setPlaceholderText("Unesite vas email");
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{

    database = QSqlDatabase::addDatabase("QMYSQL", "MyConnect");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("qt5register");
    QString mail,pass;
    mail = ui->lineEdit_3->text();
    pass = ui->lineEdit_2->text();

    if(database.open()){
           // QMessageBox::information(this,"Povezana je baza","Uspjesno");

          QSqlQuery query(QSqlDatabase::database("MyConnect"));
          query.prepare(QString("SELECT * FROM users WHERE email = :email AND sifra = :sifra"));
          query.bindValue(":email", mail);
          query.bindValue(":sifra", pass);
    if(!query.exec()){

        QMessageBox::information(this,"Greska","Neuspjesan login");
    }
    else{
        while(query.next()){
                QString imefromDB = query.value(1).toString();
            QString mailfromDB = query.value(2).toString();
            QString passfromDB = query.value(3).toString();
            if(mailfromDB == mail && passfromDB == pass){
                  this->close();
                 QMessageBox::information(this,"Uspjesno","Uspjesan login");
                 Dashboard dhboard;
                 dhboard.postaviIme(imefromDB);
                 dhboard.setModal(true);
                 dhboard.exec();
            }
            else{
            QMessageBox::information(this,"Greska","Neuspjesan login");
            }

        }


    }


    }
    else{
         QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

    }


}

