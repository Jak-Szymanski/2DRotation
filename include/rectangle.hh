#pragma once

#include "vector.hh"
#include <iostream>

class Rectangle {

  private:
    Vector Points[4];
  public:
 
    Rectangle();
    Rectangle(double [4][SIZE]);
    const double &operator () (unsigned int row, unsigned int column) const;
};

std::ostream &operator<<(std::ostream &out, Rectangle const &rec);
bool SaveRecToFile(const char *FileName, Rectangle Rec);


Rectangle::Rectangle(){
  int i,j;
  for(i=0; i<4; i++){
    for(j=0; j<SIZE; j++){
      Points[i][j] = 0;
    }
  }
}


Rectangle::Rectangle(double tmp[4][SIZE]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            Points[i][j] = tmp[i][j];
        }
    }
}


const double &Rectangle::operator () (unsigned int row, unsigned int column) const {

    if (row >= 4) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return Points[row][column];
}


std::ostream &operator<<(std::ostream &out, Rectangle const &rec){
  int i,j;
  for(i=0; i<4; i++){
    for(j=0; j<SIZE; j++){
      out << std::setw(16) << std::fixed << std::setprecision(10) << rec(i, j) << "\t";
    }
    out << std::endl;
  }
  i=0;
  for(j=0; j<SIZE; j++){
      out << std::setw(16) << std::fixed << std::setprecision(10) << rec(i, j) << "\t";
    }
    out << std::endl;
  return out;
}


bool SaveRecToFile(const char *FileName, Rectangle Rec){
       std::ofstream file;

       file.open(FileName);
       if (!file.is_open())  {
              std::cerr << ":(  Operacja otwarcia do zapisu \"" << FileName << "\"" << std::endl
	        << ":(  nie powiodla sie." << std::endl;
       return false;
  }

  file << Rec;


  file.close();
  return !file.fail();
}