#ifndef STATICA_H
#define STATICA_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QStandardItem>

namespace Ui {
class Statica;
}

class Statica : public QWidget
{
    Q_OBJECT
    
public:
    explicit Statica(QWidget *parent = 0);
    ~Statica();
    
private:
    Ui::Statica *ui;
    int n;
    QStandardItemModel *model;

public slots:
    void static_on(std::string a, int b, int c);
};

#endif // STATICA_H
