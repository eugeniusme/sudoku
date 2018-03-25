#ifndef MATR_H
#define MATR_H
#define Z 9  // какие значения могут быть в матрице (от Z-9 до Z)
#define X 0  // значения в матрице, которые показывают, проверялся ли этот элемент
#define Y -1 // инициализация матрицы
#include "matr.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <ostream>

template <class T> class matr
{

private:
    T a[9][9];

public:

    matr()
    {
    }

    matr(const matr &newM)
    {
        int i,j;
        for(i=0;i<Z;i++)
            for(j=0;j<Z;j++)
                a[i][j] = newM.a[i][j];
    }

    ~matr()
    {
    }

    bool IsSq(int i, int j, T b)        // проверка на присутсвие элемента в секторе
    {
        int di = i/3, dj = j/3;
        for (int _b(di*3), ddi = _b; ddi < _b+3; ddi++)
            for (int __b(dj*3), ddj = __b; ddj < __b+3; ddj++)
                if (a[ddi][ddj] == b)
                    return true;
        return false;
    }

    bool IsVer(int i, T b)              // проверка на присутсвие элемента в вертикали
    {
        for (int dj = 0; dj < Z; dj++)
            if (a[i][dj] == b)
                return true;
        return false;
    }

    bool IsHor(int j, T b)              // проверка на присутсвие элемента в горизонтали
    {
        for (int di = 0; di < 9; di++)
            if (a[di][j] == b)
                return true;
        return false;
    }

    bool InHor(int j, T b)              // проверка на присутсвие элемента в соседних горизонталях
    {
        int z = j/3, j1 = (j+1)%3 + (j+1)/3*(z+1), j2 = (j+2)%3 + (j+2)/3*(z+1);
        for (int di = 0; di < Z; di++)
            if (a[di][j1] == b)
                for (int dii = 0; dii < Z; dii++)
                    if (a[dii][j2] == b)
                        return true;
        return false;
    }

    bool InVer(int i, T b)              // проверка на присутсвие элемента в соседних вертикалях
    {
        int z = i/3, i1 = (i+1)%3 + (i+1)/3*(z+1), i2 = (i+2)%3 + (i+2)/3*(z+1);
        for (int dj = 0; dj < Z; dj++)
            if (a[i1][dj] == b)
                for (int dj = 0; dj < Z; dj++)
                    if (a[i2][dj] == b)
                        return true;
        return false;
    }

    void InitMas()                      // инициализация матрицы
    {
        for (int i = 0; i < Z; i++)
            for (int j = 0; j < Z; j++)
                a[i][j] = Y;
    }

    void Sudoku()                       // генерация решения
    {
        for (int i = 0; i < Z; i++)
        {
            for (int j = 0; j < Z; j++)
            {
                int c = Z;
                for (int h = Z-8; h < Z+1; h++)
                    if (IsSq(i,j,h) || IsHor(j,h) || IsVer(i,h))
                        c--;
                if (!c)
                {
                    InitMas();
                    Sudoku();
                    return;
                }
                int b = rand()%9 + 1 + X;
                while (IsSq(i,j,b) || IsHor(j,b) || IsVer(i,b))
                    b = rand()%9 + 1 + X;
                a[i][j] = b;
            }
        }
    }

    int getInfo(int i, int j)       // селектор
    {
        return a[i-1][j-1];
    }

    void setInfo(int i, int j, T p) // модификатор
    {
        a[i][j] = p;
    }

    void delets()                   // удаление элементов с целью получения поля, которое надо решить
    {
        int i,j;
        matr look;
        look.InitMas();
        int iter = 0;
        srand(time(0));

        while(iter < 81)
        {
            i = rand()%9;
            j = rand()%9;
            if(look.getInfo(i+1,j+1)==-1)
            {
                iter++;
                look.setInfo(i,j,0);
                T temp = a[i][j];
                a[i][j]=0;
                int uuy=0;
                for(int ii=0;ii<Z;ii++)
                {
                    matr solut;
                    for(int u=0;u<Z;u++)
                        for(int uj=0;uj<Z;uj++)
                            solut.setInfo(u,uj,a[u][uj]);
                    solut.setInfo(i,j,ii);
                    solut.resh();
                    if(!solut.isZero())
                        uuy++;
                }
                if(!uuy==1)
                    a[i][j]=temp;
            }
        }

        iter = 0;
        look.InitMas();
        while(iter < 81)
        {
            i = rand()%9;
            j = rand()%9;
            if(look.getInfo(i+1,j+1)==-1)
            {
                iter++;
                look.setInfo(i,j,0);
                if((InVer(i, a[i][j]) && InHor(j, a[i][j])))
                    a[i][j] = 0;
            }
        }
    }

    bool isZero()   // проверка на присутсвие в матрице нулей
    {
        int i,j;
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
                if(a[i][j]==X)
                    return true;
        return false;
    }

    void resh()     // решение данной матрицы
    {
        bool flag = false;
        int i, j;
        T n;
        while(flag == false)
        {
            int summ = 0;
            flag = true;
            for(i = 0; i < 9; i++)
                for(j = 0; j < 9; j++)
                    if(a[i][j]==X)
                    {
                        T op = X;
                        summ = 0;
                        for(n=Z-9;n<Z;n++)
                        {
                            if(!IsSq(i,j,n) && !IsHor(j,n) && !IsVer(i,n))
                                summ++, op = n;
                        }
                        if(summ == 1)
                            a[i][j]=op, flag = false;
                }
        }
    }

    bool prov() // проверка правильности решения
    {
        int i,j;
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
                if(IsVer(i, a[i][j]) || IsHor(j, a[i][j]) || IsSq(i, j, a[i][j]))
                    return false;
        return true;
    }
};

#endif // MATR_H
