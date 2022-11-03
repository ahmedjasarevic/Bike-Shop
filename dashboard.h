#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <login.h>
#include <register.h>

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    explicit Dashboard(QString text, QWidget *parent = nullptr);
    ~Dashboard();



private slots:
    void on_pushButton_clicked();

    void on_noviArtikal_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_noviArtikal_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Dashboard *ui;
     QSqlDatabase database;
      QString mailPrvi;
        int brojac = 0;
        int suma = 0;
};

#endif // DASHBOARD_H
