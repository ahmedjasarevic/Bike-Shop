#include "dashboard.h"
#include "ui_dashboard.h"
#include <login.h>
#include <ui_login.h>
#include <QPixmap>
#include <QPalette>



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

          QSqlQuery query;
          query.prepare("SELECT cijenaArtikla FROM transakcije");
          if(!query.exec()){

              QMessageBox::information(this,"Greska","Neuspjesan query");
          }
          else{
              while(query.next()){
                  suma2 +=  query.value(0).toInt();
              }
                ui->stanjeArtikalaBAM->setText("Prodani artikli (BAM) : " + QString::number(suma2));

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
      ui->stackedWidget->setCurrentIndex(0);
         if(database.open())
     {
             QSqlQueryModel * modal = new QSqlQueryModel();
             QSqlQuery* qry = new QSqlQuery(database);
             qry->prepare("select nazivArtikla,cijenaArtikla,korisnik from transakcije");
             qry->exec();
             modal->setQuery(*qry);
             ui->tableView_2->setModel(modal);

         }


         else{
               QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

      }

}


Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::postaviIme(const QString &ime){
     imePrvi = ime;
     ui->dobrodosli->setText("Dobrodosao " + imePrvi);

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
            suma +=  cijena.toInt();
            ui->stanjeBAM->setText("Trenutno stanje bicikala (BAM) : " + QString::number(suma));
        }
        else{
             QMessageBox::information(this,"Nije ubacen u bazu","Neuspjesno");
        }
    }

   else{
         QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

}
    if(database.open())
{
        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery* qry = new QSqlQuery(database);
        qry->prepare("select nazivArtikla,cijenaArtikla,korisnik from transakcije");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_2->setModel(modal);

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


void Dashboard::on_pushButton_5_clicked()
{
    if(database.open())
{
        QSqlQuery qry;

        qry.prepare("SELECT * FROM artikli WHERE naziv='"+val+"' OR cijena='"+val+"' OR ram='"+val+"' OR brzina='"+val+"' OR stanje='"+val+"'");
        if(qry.exec()){
        while(qry.next()){
         id = qry.value(0).toString();
         naziv = qry.value(1).toString();
         cijena = qry.value(2).toString();
         suma2 +=  qry.value(2).toInt();
         ui->stanjeArtikalaBAM->setText("Prodani artikli (BAM) : " + QString::number(suma2));

        }
        }

    }

    else{
          QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

 }
    if(database.open())
{
    QSqlQuery qry2;
        qry2.prepare("INSERT INTO transakcije (nazivArtikla,cijenaArtikla,korisnik)"
                    "VALUES (:nazivArtikla, :cijenaArtikla, :korisnik)");
        qry2.bindValue(":nazivArtikla", naziv);
        qry2.bindValue(":cijenaArtikla", cijena);
        qry2.bindValue(":korisnik", imePrvi);
        if(qry2.exec()){
                 suma2 +=  qry2.value(1).toInt();
                  ui->stanjeArtikalaBAM->setText("Prodani artikli (BAM) : " + QString::number(suma2));
                    QMessageBox::information(this,"Ubacenu u bazu","Uspjesno");
                }

    }
    else{
          QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

 }


    if(database.open())
{
    QSqlQuery qry3;
      qry3.prepare("DELETE FROM artikli WHERE id='"+id+"'");
                   if(qry3.exec()){
                   QMessageBox::information(this,"Uspjesno","Prodan artikal");
    }
    }
    else{
          QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

 }


}




void Dashboard::on_tableView_activated(const QModelIndex &index)
{
    val  = ui->tableView->model()->data(index).toString();
    const QColor hlClr = Qt::red;
    const QColor txtClr = Qt::white;

    QPalette p = palette();
    p.setColor(QPalette::Highlight, hlClr);
    p.setColor(QPalette::HighlightedText, txtClr);
    setPalette(p);



}


void Dashboard::on_tableView_clicked(const QModelIndex &index)
{
    val  = ui->tableView->model()->data(index).toString();
    const QColor hlClr = Qt::red;
    const QColor txtClr = Qt::white;

    QPalette p = palette();
    p.setColor(QPalette::Highlight, hlClr);
    p.setColor(QPalette::HighlightedText, txtClr);
    setPalette(p);

}


void Dashboard::on_ucitajTransakcije_clicked()
{


    if(database.open())
{
        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery* qry = new QSqlQuery(database);
        qry->prepare("select nazivArtikla,cijenaArtikla,korisnik from transakcije");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_2->setModel(modal);
        suma +=  qry->value(1).toInt();
        ui->stanjeBAM->setText("Trenutno stanje bicikala (BAM) : " + QString::number(suma));

    }


    else{
          QMessageBox::information(this,"Nije povezana baza","Baza nije povezana");

 }

 ui->stanjeArtikalaBAM->setText("Prodani artikli (BAM) : " + QString::number(suma2));

}


void Dashboard::on_pushButton_6_clicked()
{
    this->close();
}

