#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <login.h>
#include <register.h>
#include "ui_login.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    void postaviIme(const QString &ime);
    ~Dashboard();



private slots:
    void on_pushButton_clicked();

    void on_noviArtikal_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_noviArtikal_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();



    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_ucitajTransakcije_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Dashboard *ui;
     QSqlDatabase database;
      QString imePrvi;
        int brojac = 0;
        int suma = 0,suma2 = 0;
          QString naziv,cijena,val,id;
};

#endif // DASHBOARD_H
