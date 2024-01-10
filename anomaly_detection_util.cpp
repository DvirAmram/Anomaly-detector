//Niv Nahman 318012564 and Dvir Amram 318192200
#include <iostream>
#include "anomaly_detection_util.h"
#include <math.h>
// returns the average of the arr
static float avg (float* a, int size)
{
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum = sum + a[i];
    }
    float avg = sum/size;
    return avg;
}
//returns the variance of X and Y
float var(float* x, int size)
{
    float expectation_value;
    float sum = 0;
    expectation_value = avg(x, size);
    for (int i = 0; i < size; ++i) {
        sum = sum + float(pow(x[i] - expectation_value,2));
    }
    return (sum/size);
}
float cov(float* x, float* y, int size)
{
    float *z = new float [size];
    for (int i = 0; i < size; ++i) {
        z[i]=x[i]*y[i];
    }
    float cov = (avg(z, size) - (avg(x, size)*avg(y,size)));
    return cov;
}
// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size)
{
    float p = (cov(x,y,size)) / (sqrt(var(x, size))*sqrt(var(y, size)));
    return p;
}
//builds the linear regression and returns the line equation
Line linear_reg(Point** points, int size)
{
    float *x = new float [size];
    float *y = new float [size];
    for (int i = 0; i < size; ++i) {
        x[i] = points[i]->x;
    }
    for (int i = 0; i < size; ++i) {
        y[i]=points[i]->y;
    }
    float a = cov(x,y,size)/var(x,size);
    float b = avg(y,size)-a*avg(x,size);
    Line l;
    l.a = a;
    l.b = b;
    return l;
}
float dev(Point p,Point** points, int size)
{
    Line l = linear_reg(points, size);
    return abs(p.y - l.f(p.x));
}
// returns the deviation between point p and the line
float dev(Point p,Line l)
{
    if((p.y - l.f(p.x) < 0))
        return -1 *  (p.y - l.f(p.x));
    return (p.y - l.f(p.x));
}