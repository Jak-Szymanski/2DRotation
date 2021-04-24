
#include "../include/rectangle.hh"
#include "../include/vector.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 
#define MIN_DIFF  0.01


Rectangle::Rectangle(){
  for(int i=0; i<4; i++){
    for(int j=0; j<SIZE; j++){
      Points[i][j] = 0;
    }
  }
}


Rectangle::Rectangle(const Rectangle &rec){
  for(int i=0; i<4; i++){
    for(int j=0; j<SIZE; j++){
      Points[i][j] = rec(i, j);
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


double &Rectangle::operator () (unsigned int row, unsigned int column){

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

bool Rectangle::operator == (const Rectangle &rec) const{
  for(int i=0; i<4; i++){
    for(int j=0; j<SIZE; j++){
      if(abs(Points[i][j] - rec(i, j) >= MIN_DIFF)){
        return 0;
      }
    }
  }
  return 1; 
}


std::ostream &operator<<(std::ostream &out, Rectangle const &rec){
  int i, j;
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


bool SaveRecToFile(const char *FileName, Rectangle &Rec){
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


Rectangle Rectangle::Rotate(double degrees, int iterations){
  Matrix MRotation;
  MRotation.Rotation(degrees);

  for(; iterations > 0; iterations--){
    for(int i=0; i<4; i++){
      Points[i] = MRotation * Points[i];
    }
  }
  return *this;
}


void Rectangle::CompareSides(){
  double a, b, c, d;

  a = Distance(Points[0], Points[1]);
  b = Distance(Points[1], Points[2]);
  c = Distance(Points[2], Points[3]);
  d = Distance(Points[3], Points[0]);

  if (a > b){
    if(abs(a-c) < MIN_DIFF){
      std::cout << std::endl << ":) Dłuższe przeciwległe boki są sobie równe." << std::endl;
    } else {
      std::cout << " :O Dłuższe przeciwległe boki nie są sobie równe!!!" << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << a << std::endl;
    std::cout << "Długość drugiego boku: " << c << std::endl;

    if(abs(b-d) < MIN_DIFF){
      std::cout << std::endl << ":) Krótsze przeciwległe boki są sobie równe." << std::endl;
    } else {
      std::cout << " :O Krótsze przeciwległe boki nie są sobie równe!!!" << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << b << std::endl;
    std::cout << "Długość drugiego boku: " << d << std::endl;
  } else {
    if(abs(b-d) < MIN_DIFF){
      std::cout << std::endl << ":) Dłuższe przeciwległe boki są sobie równe." << std::endl;
    } else {
      std::cout << " :O Dłuższe przeciwległe boki nie są sobie równe!!!" << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << b << std::endl;
    std::cout << "Długość drugiego boku: " << d << std::endl;

    if(abs(a-c) < MIN_DIFF){
      std::cout << std::endl << ":) Krótsze przeciwległe boki są sobie równe." << std::endl;
    } else {
      std::cout << " :O Krótsze przeciwległe boki nie są sobie równe!!!" << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << a << std::endl;
    std::cout << "Długość drugiego boku: " << c << std::endl;   
  }
}


Rectangle Rectangle::Move(Vector v){

  for(int i=0; i<4; i++){
    Points[i] = Points[i] + v;
  }

  return *this;
}