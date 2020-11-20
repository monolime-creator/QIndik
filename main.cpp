#include "mainwindow.h"
#include "customindikator.h"
#include <QApplication>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *w = new QWidget;

    CustomIndikator *Indik1 = new CustomIndikator;
    Indik1->setDefaultValues(false,true,true);
    CustomIndikator *Indik2 = new CustomIndikator;
    QHBoxLayout *Lay = new QHBoxLayout;

   Lay->setSpacing(2);

    Lay->addWidget(Indik1);
    Lay->addWidget(Indik2);


    w->setLayout(Lay);

     w->setStyleSheet("* {background-color: rgb(62, 70, 73)}");

    w->show();

    return a.exec();
}
