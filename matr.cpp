#include "matr.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <ostream>

matr::matr()
{
}

matr::matr(const matr &newM)
{
    int i,j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            a[i][j] = newM.a[i][j];
}

matr::~matr()
{
}

bool matr::IsSq(int i, int j, int b)
{
    int di = i/3, dj = j/3;
    for (int _b(di*3), ddi = _b; ddi < _b+3; ddi++)
        for (int __b(dj*3), ddj = __b; ddj < __b+3; ddj++)
            if (a[ddi][ddj] == b)
                return true;
    return false;
}

bool matr::IsVer(int i, int b)
{
    for (int dj = 0; dj < 9; dj++)
        if (a[i][dj] == b)
            return true;
    return false;
}

bool matr::IsHor(int j, int b)
{
    for (int di = 0; di < 9; di++)
        if (a[di][j] == b)
            return true;
    return false;
}

bool matr::InHor(int j, int b)
{
    int z = j/3, j1 = (j+1)%3 + (j+1)/3*(z+1), j2 = (j+2)%3 + (j+2)/3*(z+1);
    for (int di = 0; di < 9; di++)
        if (a[di][j1] == b)
            for (int dii = 0; dii < 9; dii++)
                if (a[dii][j2] == b)
                    return true;
    return false;
}

bool matr::InVer(int i, int b)
{


    int z = i/3, i1 = (i+1)%3 + (i+1)/3*(z+1), i2 = (i+2)%3 + (i+2)/3*(z+1);
    for (int dj = 0; dj < 9; dj++)
        if (a[i1][dj] == b)
            for (int dj = 0; dj < 9; dj++)
                if (a[i2][dj] == b)
                    return true;
    return false;
}

void matr::InitMas()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            a[i][j] = -1;
}

void matr::Sudoku()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int c = 9;
            for (int h = 1; h < 10; h++)
                if (IsSq(i,j,h) || IsHor(j,h) || IsVer(i,h))
                    c--;
            if (!c)
            {
                InitMas();
                Sudoku();
                return;
            }
            int b = rand()%9 + 1;
            while (IsSq(i,j,b) || IsHor(j,b) || IsVer(i,b))
                b = rand()%9 + 1;
            a[i][j] = b;
        }
    }
}

int matr::getInfo(int i, int j)
{
    return a[i-1][j-1];
}

void matr::setInfo(int i, int j, int p)
{
    a[i][j] = p;
}

void matr::delets()
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
            int temp = a[i][j];
            a[i][j]=0;
            int uuy=0;
            for(int ii=0;ii<9;ii++)
            {
                matr solut;
                for(int u=0;u<9;u++)
                    for(int uj=0;uj<9;uj++)
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

bool matr::isZero()
{
    int i,j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            if(a[i][j]==0)
                return true;
    return false;
}

void matr::resh()
{
    bool flag = false;
    int i,j,n;
    while(flag == false)
    {
        int summ = 0;
        flag = true;
        for(i = 0; i < 9; i++)
            for(j = 0; j < 9; j++)
                if(a[i][j]==0)
                {
                    int op = 0;
                    summ = 0;
                    for(n=1;n<10;n++)
                    {
                        if(!IsSq(i,j,n) && !IsHor(j,n) && !IsVer(i,n))
                            summ++, op = n;
                    }
                    if(summ == 1)
                        a[i][j]=op, flag = false;
            }
    }
}

bool matr::prov()
{
    int i,j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            if(!IsVer(i, a[i][j]) || !IsHor(j, a[i][j]) || !IsSq(i, j, a[i][j]))
                return false;
    return true;
}
