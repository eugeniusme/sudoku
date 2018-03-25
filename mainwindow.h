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
    matr <int> sudoku;      // ������� ��������
    Form *window;           // ���� �������
    Registr *windowR;       // ���� ����������
    Statica *windowS;       // ���� ����������
    Gamers *windowG;        // ���� �����
    std::string gamers[mex]; // ������ ��� �������
    int vin[mex], lose[mex]; // ������� ��������� � ���������� �������
    int n;                   // ���������� ������������������ �������
    std::string gamer;       // ������� �����

signals:
    void setList(std::string, int, int);    // ������ ���������� � ������� ����������

private slots:
    void print_s();                 // ����� �� �����
    void on_actionAboutProgram();   // �������

    void new_game();                // ������ ����� ����
    void proverty();                // �������� �������
    void registration();            // �����������
    void registra(QString gmer);
    void vibor_igroka();            // ���� � ������� ��� ������
    void choose(std::string a);
    void statistika();              // ����������

    void save_info();               // ������ � ���� - ���������� ����������
    void open_info();               // ������ �� ����� - ���������� ����������
};

#endif // MAINWINDOW_H
