#ifndef GAMERS_H
#define GAMERS_H

#include <QWidget>

namespace Ui {
class Gamers;
}

class Gamers : public QWidget
{
    Q_OBJECT
    
public:
    explicit Gamers(QWidget *parent = 0);
    ~Gamers();

signals:
    void setGamer(std::string);
    
private:
    Ui::Gamers *ui;

private slots:
    void into();
};

#endif // GAMERS_H
