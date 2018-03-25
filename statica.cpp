#include "statica.h"
#include "ui_statica.h"
#include "QStandardItemModel"
#include "QStandardItem"
//#include <QTableWidgetItem>
Statica::Statica(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statica)
{
    n = 0;
    ui->setupUi(this);

    model = new QStandardItemModel;
    QStringList horizontalHeader;

    horizontalHeader.append("Gamer");
    horizontalHeader.append("Wins");
    horizontalHeader.append("Lose");
    horizontalHeader.append("Percent, %");

    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

}

Statica::~Statica()
{
    delete ui;
}

void Statica::static_on(std::string a, int b, int c)
{
    QStandardItem *itemG, *itemW, *itemL, *itemP;
    itemG = new QStandardItem(QString::fromStdString(a));
    itemW = new QStandardItem(QString::number(b));
    itemL = new QStandardItem(QString::number(c));
    itemP = new QStandardItem(QString::number(b*100/(c+b)));
    model->setItem(n, 0, itemG);
    model->setItem(n, 1, itemW);
    model->setItem(n, 2, itemL);
    model->setItem(n, 3, itemP);
    ui->tableView->setModel(model);
    n++;
}
