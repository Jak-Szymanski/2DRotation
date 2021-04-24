#pragma once

#include "vector.hh"
#include "matrix.hh"
#include <iostream>




class Rectangle {

  private:
    Vector Points[4];
  public:
 
    Rectangle();

    Rectangle(const Rectangle &rec);

    Rectangle(double [4][SIZE]);

    double &operator () (unsigned int row, unsigned int column);

    const double &operator () (unsigned int row, unsigned int column) const;

    bool operator == (const Rectangle &rec) const;

    Rectangle Rotate(double degrees, int iterations);

    void CompareSides();
    
    Rectangle Move(Vector v);
};

std::ostream &operator<<(std::ostream &out, Rectangle const &rec);
bool SaveRecToFile(const char *FileName, Rectangle &Rec);



  













