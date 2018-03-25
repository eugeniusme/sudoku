#include "w.h"
#include "ui_w.h"
#include <QMessageBox>
#include "mainwindow.h"

w::w(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::w)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

w::~w()
{
    delete ui;
}


// закрытие окна
void w::on_pushButton_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Attention!", "Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        close();
    }
}
