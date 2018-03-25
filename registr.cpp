#include "registr.h"
#include "ui_registr.h"

Registr::Registr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registr)
{
    ui->setupUi(this);

    ui->label->setAlignment(Qt::AlignHCenter);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(bth_pressed()));
}

Registr::~Registr()
{
    delete ui;
}

void Registr::bth_pressed()
{
    emit setName(ui->lineEdit->text());
}
