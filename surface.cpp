#include "surface.h"

Surface::Surface()
{
    setCountOfPoint(countOfPoint);
    CalculateArray();
}
Surface::~Surface()
{
    delete [] arrayOfPoint;
}

double Surface::CalculateZ(double x, double y)
{
//    return pow(x, 3) -x * y - pow(y, 2);
    return pow(x,2) + y;
}

void Surface::CalculateArray()
{
    for (int i = 0; i < countOfPoint * 3; i += 3)
        {
            int number = i / 3;
            double x = number / ((int)sqrt(countOfPoint)) * size / ((int)sqrt(countOfPoint) - 1) - size / 2;
            double y = number % ((int)sqrt(countOfPoint)) * size / ((int)sqrt(countOfPoint) - 1) - size / 2;
            double z = CalculateZ(x, y);

            arrayOfPoint[i] = x;
            arrayOfPoint[i + 1] = y;
            arrayOfPoint[i + 2] = z;
        }
}

void Surface::setCountOfPoint(int value)
{
    countOfPoint = value;
    arrayOfPoint = new double[countOfPoint * 3];
    CalculateArray();
}

void Surface::setSize(double value)
{
    size = value;
    CalculateArray();
}

double Surface::getSize() const
{
    return size;
}

int Surface::getCountOfPoint() const
{
    return countOfPoint;
}
