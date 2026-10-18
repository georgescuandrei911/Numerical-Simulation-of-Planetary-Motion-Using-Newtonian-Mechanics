#include "agmath.h"

double pow(double x, int f)
{
    double ans = 1;
    for(int i=0; i<f; i++)
        ans *= x;
    return ans;
}

double fact(int x)
{
    double ans = 1;
    for(int i=2; i<=x; i++)
        ans *= i;
    return ans;
}

double sin(double x)
{
    double val = x;
    double term = x;

    for(int k = 1; k < MAX; k++)
    {
        term *= -x*x / ((2.0*k)*(2.0*k+1.0));
        val += term;
    }

    return val;
}

double root(double x)
{

    if(x <  0) return -1;
    if(x == 0) return 0;
    if(x == 1) return 1;

    double x_next = 1;

    for(int i = 0; i < MAX * 5; i++) x_next = (x_next + x / x_next) / 2;

    return x_next;

}

int sign(double x)
{

    if(x >= 0) return 1;
    else return -1;

}

double abs(double x)
{

    if(x < 0)return -x;
    else return x;

}