#ifndef STAT_H
#define STAT_H

#include <QWidget>

namespace Ui {
class stat;
}

class stat : public QWidget
{
    Q_OBJECT
    
public:
    explicit stat(QWidget *parent = 0);
    ~stat();
    
private:
    Ui::stat *ui;
};

#endif // STAT_H
