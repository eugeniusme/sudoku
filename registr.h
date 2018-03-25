#ifndef REGISTR_H
#define REGISTR_H

#include <QWidget>

namespace Ui {
class Registr;
}

class Registr : public QWidget
{
    Q_OBJECT
    
public:
    explicit Registr(QWidget *parent = 0);
    ~Registr();
    
private:
    Ui::Registr *ui;

signals:
    void setName(QString gmer);

private slots:
    void bth_pressed();
};

#endif // REGISTR_H
