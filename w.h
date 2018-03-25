#ifndef W_H
#define W_H

#include <QWidget>

namespace Ui {
class w;
}

class w : public QWidget
{
    Q_OBJECT
    
public:
    explicit w(QWidget *parent = 0);
    ~w();
    
private:
    Ui::w *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // W_H
