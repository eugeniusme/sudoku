#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matr.h"
#include <cstring>
#include <ctime>
#include <QAction>
#include <QLineEdit>
#include "registr.h"
#include <QWidget>
#include <QMessageBox>
#include <QListWidget>
#include <QVBoxLayout>
#include <fstream>
#include <sstream>
#include <QStringList>
#include "statica.h"
#include "gamers.h"

#define ASC '1'

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    n = 0;
    ui->setupUi(this);
    srand(time(0));
    sudoku.InitMas();
    sudoku.Sudoku();

    QList <QLineEdit *> list = this->findChildren<QLineEdit*>();
    QRegExp float_exp("^?[1-9]");       // допустимые значени€ дл€ ввода в €чейки
    foreach(QLineEdit *x, list)
    {
        x->setValidator(new QRegExpValidator(float_exp, this));
        x->setEnabled(false);
    }

    QAction* act = ui->actionAboutProgram;
    connect(act, SIGNAL(triggered()), this, SLOT(on_actionAboutProgram()));

    connect(ui->pushButton_new, SIGNAL(clicked()), this, SLOT(new_game()));
    connect(ui->pushButton_pro, SIGNAL(clicked()), this, SLOT(proverty()));
    connect(ui->pushButton_reg, SIGNAL(clicked()), this, SLOT(registration()));
    connect(ui->pusButton_stat, SIGNAL(clicked()), this, SLOT(statistika()));
    connect(ui->pushButton_vib, SIGNAL(clicked()), this, SLOT(vibor_igroka()));

    open_info();    // статистика загружаетс€

    if(n==0)        // а если данных о ней нет, то кнопки выбора игрока и статистики станов€тс€ неактивными
    {
        ui->pusButton_stat->setEnabled(false);
        ui->pushButton_vib->setEnabled(false);
    }
    ui->pushButton_pro->setEnabled(false);
    ui->pushButton_new->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::registra(QString gmer)
{
    gamer = gmer.toStdString();
    std::string name = "Hello, " + gamer;
    ui->label_2->setText(QString::fromStdString(name) + QString::number(n));
    if(n == mex)
    {
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.setInformativeText("Igrokov slishkom mnogo!");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        int ret = msgBox.exec();
        gamer = "";
    }
    else
    {
        bool flag = false;
        for(int i = 0; i < n; i++)
            if (gamer == gamers[i])
                flag = true;
        if(flag)
        {
            QMessageBox msgBox;
            msgBox.setText("Error!");
            msgBox.setInformativeText("Igrok s zadannim imenem yzhe sushestvuet!");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            int ret = msgBox.exec();
        }
        else
        {
            gamers[n] = gamer;
            vin[n] = 0;
            lose[n] = 0;
            n++;
            ui->pushButton_new->setEnabled(true);
        }

    }
    ui->pusButton_stat->setEnabled(true);
    ui->pushButton_vib->setEnabled(true);
}

void MainWindow::choose(std::string a)
{
    int ii=-1;
    for(int i=0;i<n;i++)
        if(gamers[i]==a)
            ii=i;
    if(ii!=-1)
    {
        gamer = gamers[ii];
        std::string name = "Hello, " + gamer;
        ui->label_2->setText(QString::fromStdString(name));
        ui->pushButton_new->setEnabled(true);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.setInformativeText("Gamer not found!!");
        msgBox.setStandardButtons(QMessageBox::Cancel);
    }
}

// функци€ перевода из типа double в тип string
std::string ftoa(const double& x)
{
  std::ostringstream o;
  if (!(o << x)) return "ERROR";
  return o.str();
}

void MainWindow::save_info()
{
    int cash=0;
    std::ofstream file;
    char d[100] = "records.txt";
    file.open(d);
    file << n;
    for(int i=0; i<n; i++)
    {
        const char* d;
        d = gamers[i].c_str();
        std::string s = "";
        int j = 0;
        while(j < strlen(d))
        {
            //cash += int(d[j]);
            s += int(d[j] + ASC);
            j++;
        }
        file << "\n" <<  s;

        d = ftoa(vin[i]).c_str();
        s = "";
        j = 0;
        while(j < strlen(d))
        {
            cash += int(d[j]);
            s += int(d[j] + ASC);
            j++;
        }
        file << "\n" <<  s;

        d = ftoa(lose[i]).c_str();
        s = "";
        j=0;
        while(j < strlen(d))
        {
            cash += int(d[j]);
            s += int(d[j] + ASC);
            j++;
        }
        file << "\n" <<  s;
    }
    file << "\n" << cash;
    file.close();
}

size_t _atoi(const char * str)
{
   size_t res = 0;
   for (; *str; res += *str++ - '0')
      res *= 10;
   return res;
}

void MainWindow::open_info()
{
    int cash=0;
    char d[100] = "records.txt";
    std::ifstream myfile(d);
    std::string line;
    if (myfile.is_open())
    {
        getline(myfile, line);
        n = _atoi(line.c_str());

        for(int i=0; i<n; i++)
        {
            getline(myfile, line);

            std::string str;
            const char* d;
            d = line.c_str();
            str = "";
            int j = 0;
            while(j < strlen(d))
            {
                //cash += int(d[j] - ASC);
                str += int(d[j] - ASC);
                j++;
            }

            gamers[i] = str;
            getline(myfile, line);

            d = line.c_str();
            str = "";
            j = 0;
            while(j < strlen(d))
            {
                cash += int(d[j] - ASC);
                str += int(d[j] - ASC);
                j++;
            }
            vin[i] = _atoi(str.c_str());

            getline(myfile, line);
            d = line.c_str();
            str = "";
            j = 0;
            while(j < strlen(d))
            {
                cash += int(d[j] - ASC);
                str += int(d[j] - ASC);
                j++;
            }
            lose[i] = _atoi(str.c_str());
        }
        getline(myfile, line);
        int ca = _atoi(line.c_str());
        if(ca != cash)
        {
            QMessageBox msgBox;
            msgBox.setText("Error!");
            msgBox.setInformativeText("V faile bilo izmen!");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            int ret = msgBox.exec();
        }
        myfile.close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.setInformativeText("File was not find!");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        int ret = msgBox.exec();
        //save_info();
    }
}

void MainWindow::registration()
{
    Registr *windowR;
    windowR = new Registr;
    windowR->setMinimumHeight(260);
    windowR->setMaximumHeight(260);
    windowR->setMinimumWidth(460);
    windowR->setMaximumWidth(460);
    windowR->show();
    connect(windowR, SIGNAL(setName(QString)), this, SLOT(registra(QString)));
}


void MainWindow::statistika()
{
    Statica *windowS = new Statica;
    windowS->setMinimumHeight(260);
    windowS->setMaximumHeight(260);
    windowS->setMinimumWidth(460);
    windowS->setMaximumWidth(460);
    windowS->show();

    connect(this, SIGNAL(setList(std::string, int, int)), windowS, SLOT(static_on(std::string, int, int)));

    for(int i = 0; i<n; i++)
    {
        emit setList(gamers[i], vin[i], lose[i]);
    }
}

void MainWindow::vibor_igroka()
{
    Gamers *windowG;
    windowG = new Gamers;
    windowG->setMinimumHeight(260);
    windowG->setMaximumHeight(260);
    windowG->setMinimumWidth(460);
    windowG->setMaximumWidth(460);
    windowG->show();
    connect(windowG, SIGNAL(setGamer(std::string)), this, SLOT(choose(std::string)));
}

void MainWindow::new_game()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Attention!", "New game is coming", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QList <QLineEdit *> list = this->findChildren<QLineEdit*>();
        foreach(QLineEdit *x, list)
        {
            x -> setEnabled(true);
        }
        sudoku.InitMas();
        sudoku.Sudoku();
        sudoku.delets();
        print_s();
        ui->pushButton_pro->setEnabled(true);
    }
}

void MainWindow::proverty()
{
    int i = 0;
    int j = 0;

    QList <QLineEdit *> list = this->findChildren<QLineEdit*>();
    foreach(QLineEdit *x, list)
    {
        if(!x->text().isEmpty())
            sudoku.setInfo(i/9, j%9, x->text().toDouble());
        i++;
        j++;
    }
    if (!sudoku.prov() || sudoku.isZero())
    {
        QMessageBox msgBox;
        msgBox.setText("It`s wrong!");
        msgBox.setInformativeText("Unfortunately, the decision is incorrect");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        int ret = msgBox.exec();
        bool flag=false;
        i = 0;
        while (!flag && i<n)
        {
            if(gamers[i]==gamer)
                flag = true;
            i++;
        }
        if (flag)
            lose[i-1]++;
        else
            gamers[n]=gamer, vin[n]=0, lose[n]=1, n++;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Congratulations!");
        msgBox.setInformativeText("You're absolutely right!");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        int ret = msgBox.exec();
        bool flag=false;
        i = 0;
        while (!flag && i<n)
        {
            if(gamers[i]==gamer)
                flag = true;
            i++;
        }
        if (flag)
            vin[i-1]++;
        else
            gamers[n]=gamer, vin[n]=0, lose[n]=1, n++;
    }
    save_info();
    new_game();
}

void MainWindow::print_s()
{
    int i = 0;
    int j = 0;

    QList <QLineEdit *> list = this->findChildren<QLineEdit*>();
    foreach(QLineEdit *x, list)
    {
        x ->setAlignment(Qt::AlignHCenter);
        if(sudoku.getInfo(i/9 + 1, j%9 + 1)!=0)
            x->setText(QString::number(sudoku.getInfo(i/9 + 1,j%9 + 1))), x -> setEnabled(false);
        else
            x->clear();
        i++;
        j++;
    }
}

//событи€ дл€ вывода информационных окон
//справка
void MainWindow::on_actionAboutProgram()
{
    window = new Form;
    window->setMinimumHeight(260);
    window->setMaximumHeight(260);
    window->setMinimumWidth(460);
    window->setMaximumWidth(460);
    window->show();
    connect(window, SIGNAL(close()), this, SLOT(on_close_window_cl()) );
}
