#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define mex 100 //INT_MAX
#include <QMainWindow>
#include "form.h"
#include "about.h"
#include <QLabel>
#include "registr.h"
#include <QStringList>
#include "statica.h"
#include "gamers.h"
#include "matr.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    matr <int> sudoku;      // матрица значений
    Form *window;           // окно справки
    Registr *windowR;       // окно регистации
    Statica *windowS;       // окно статистики
    Gamers *windowG;        // окно входа
    std::string gamers[mex]; // массив имён игроков
    int vin[mex], lose[mex]; // массивы выигрышей и проигрышей игроков
    int n;                   // количество зарегистрированных игроков
    std::string gamer;       // текущий игрок

signals:
    void setList(std::string, int, int);    // сигнал соединения с классом статистики

private slots:
    void print_s();                 // вывод на экран
    void on_actionAboutProgram();   // справка

    void new_game();                // начало новой игры
    void proverty();                // проверка решения
    void registration();            // регистрация
    void registra(QString gmer);
    void vibor_igroka();            // вход в систему под именем
    void choose(std::string a);
    void statistika();              // статистика

    void save_info();               // запись в файл - сохранение статистики
    void open_info();               // чтение из файла - извлечение статистики
};

#endif // MAINWINDOW_H
