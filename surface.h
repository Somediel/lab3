#ifndef FUNCTION_H
#define FUNCTION_H
#include <math.h>
class Surface // z = x^2 + y
{
public:
    Surface();
    ~ Surface();

    double CalculateZ(double x, double y);
    void CalculateArray();
    void setCountOfPoint(int value);
    int getCountOfPoint() const;
    void setSize(double value);
    double getSize() const;

    double *arrayOfPoint;

private:
    double size = 2;
    int countOfPoint = 10000;
};

#endif // FUNCTION_H
