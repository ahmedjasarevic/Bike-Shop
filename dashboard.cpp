#include "dashboard.h"
#include "ui_dashboard.h"
#include <QPixmap>
#include <QPalette>

Dashboard::Dashboard(QString text, QWidget *parent) : QDialog(parent)
{
    mailPrvi = text;
}

Dashboard::Dashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
         ui->lineIme->setPlaceholderText("Unesite naziv bicikla");
    ui->lineCijena->setPlaceholderText("Unesite cijenu bicikla");
     ui->lineRam->setPlaceholderText("Unesite velicinu rama");
      ui->lineStanje->setPlaceholderText("Unesite stanje bicikla(nov,polovan)");
       ui->lineBrzine->setPlaceholderText("Unesite broj brzina ");
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("qt5register");
    if(database.open())
{
        QString welcome;
         QSqlQuery query("SELECT ime FROM users WHERE email = :email");
         query.bindValue(":email", mailPrvi);
         while (query.next()) {
             welcome.append("Dobrodosao " + query.value(0).toString() + " ");

         }
         ui->dobrodosli->setText(welcome);
    }
      ui->stackedWidget->setCurrentIndex(0);
      if(database.open())
  {

          QSqlQuery qry;
          qry.prepare("SELECT * FROM artikli");
          qry.exec();
            ui->stanje->setText("Trenutno stanje bicikala: " + QString::number(qry.size()));
          }
      if(database.open())
  {

          QSqlQuery query;
          query.prepare("SELECT cijena FROM artikli");
          if(!query.exec()){

              QMessageBox::information(this,"Greska","Neuspjesan query");
          }
          else{
              while(query.next()){
                  suma +=  query.value(0).toInt();
              }
              ui->stanjeBAM->setText("Trenutno stanje bicikala (BAM) : " + QString::number(suma));

      }
}
      if(database.open())
  {
          QSqlQueryModel * modal = new QSqlQueryModel();
          QSqlQuery* qry = new QSqlQuery(database);
          qry->prepare("select naziv,cijena,ram,brzina,stanje from artikli");
          qry->exec();
          modal->setQuery(*qry);
          ui->tableView->setModel(modal);


      }
      else{
            QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

   }


}


Dashboard::~Dashboard()
{
    delete ui;
}



void Dashboard::on_noviArtikal_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Dashboard::on_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void Dashboard::on_pushButton_2_clicked()
{

    if(database.open())
{
        QString naziv,stanje,cijena,ram,brzina;
        naziv = ui->lineIme->text();
        stanje = ui->lineStanje->text();
        cijena = ui->lineCijena->text();
        ram = ui->lineRam->text();
        brzina = ui->lineBrzine->text();
        QSqlQuery qry;
        qry.prepare("INSERT INTO artikli (naziv,cijena,ram,brzina,stanje)"
                    "VALUES (:naziv, :cijena, :ram, :brzina, :stanje)");
        qry.bindValue(":naziv", naziv);
        qry.bindValue(":cijena", cijena);
        qry.bindValue(":ram", ram);
        qry.bindValue(":brzina", brzina);
        qry.bindValue(":stanje", stanje);

        if(qry.exec()){
            QMessageBox::information(this,"Ubacenu u bazu","Uspjesno");
            suma +=  qry.value(1).toInt();
            ui->stanjeBAM->setText("Trenutno stanje bicikala (BAM) : " + QString::number(suma));
        }
        else{
             QMessageBox::information(this,"Nije ubacen u bazu","Neuspjesno");
        }

}
   else{
         QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

}

}


void Dashboard::on_pushButton_3_clicked()
{

    if(database.open())
{
        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery* qry = new QSqlQuery(database);
        qry->prepare("select naziv,cijena,ram,brzina,stanje from artikli");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->stanje->setText("Trenutno stanje bicikala: " + QString::number(qry->size()));
    }


    else{
          QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

 }


}



void Dashboard::on_noviArtikal_2_clicked()
{
        ui->stackedWidget->setCurrentIndex(2);
}


void Dashboard::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

