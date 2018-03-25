#include "gamers.h"
#include "ui_gamers.h"

Gamers::Gamers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gamers)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignHCenter);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(into()));
}

Gamers::~Gamers()
{
    delete ui;
}

void Gamers::into()
{
    emit setGamer(ui->lineEdit->text().toStdString());
}
