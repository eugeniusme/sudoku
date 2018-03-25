// класс, отвечающий за окно с информацией о программе

#ifndef FORM_H
#define FORM_H


#include <QWidget>

namespace Ui {
class about;
}

class about : public QWidget
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

private:
    Ui::about *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // FORM_H
