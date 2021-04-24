#pragma once

#include "size.hh"
#include <math.h>
#include <iostream>

class Vector {

private:

    double size[SIZE];     //Tablica wektora

public:

    Vector();

    Vector(double [SIZE]);

    Vector (const Vector &v);

    Vector operator + (const Vector &v);

    Vector operator - (const Vector &v);

    Vector operator * (const double &tmp);

    Vector operator / (const double &tmp);

    Vector operator = (const Vector &v);

    const double &operator [] (int index) const;

    double &operator [] (int index);

    bool operator == (const Vector &v) const;

};

    double Distance (const Vector v1, const Vector v2);

std::ostream &operator << (std::ostream &out, Vector const &tmp);

std::istream &operator >> (std::istream &in, Vector &tmp);
