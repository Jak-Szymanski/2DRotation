
#include "../include/rectangle.hh"
#include "../include/vector.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <fstream> 
#define MIN_DIFF  0.01

/******************************************************************************
 |  Konstruktor klasy Rectangle.                                              |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Prostokąt wypelniony wartoscia 0.                                     |
 */

Rectangle::Rectangle(){
  for(int i=0; i<4; i++){
    for(int j=0; j<SIZE; j++){
      Points[i][j] = 0;
    }
  }
}

/******************************************************************************
 |  Konstruktor parametryczny klasy Rectangle.                                |
 |  Argumenty:                                                                |
 |      rec - prostokąt                                                       |
 |  Zwraca:                                                                   |
 |      Prostokąt wypelniony wartosciami podanymi w argumencie.               |
 */

Rectangle::Rectangle(const Rectangle &rec){
  for(int i=0; i<4; i++){
    for(int j=0; j<SIZE; j++){
      Points[i][j] = rec(i, j);
    }
  }
}


/******************************************************************************
 |  Konstruktor parametryczny klasy Rectangle.                                |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Prostokąt wypelniony wartosciami podanymi w argumencie.               |
 */

Rectangle::Rectangle(double tmp[4][SIZE]) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      Points[i][j] = tmp[i][j];
    }
  }
}


/******************************************************************************
 |  Funktor Prostokąta                                                        |
 |  Argumenty:                                                                |
 |      row - numer wiersza (który punkt).                                    |
 |      column - numer kolumny (które współrzędne punktu).                    |
 |  Zwraca:                                                                   |
 |      Wartosc w danym miejscu tablicy jako stała.                           |
 */

const double &Rectangle::operator () (unsigned int row, unsigned int column) const {

    if (row >= 4) {
      throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
      throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return Points[row][column];
}


/******************************************************************************
 |  Funktor Prostokąta                                                        |
 |  Argumenty:                                                                |
 |      row - numer wiersza (który punkt).                                    |
 |      column - numer kolumny (które współrzędne punktu).                    |
 |  Zwraca:                                                                   |
 |      Wartosc w danym miejscu tablicy.                                      |
 */

double &Rectangle::operator () (unsigned int row, unsigned int column){

    if (row >= 4) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return Points[row][column];
}


/******************************************************************************
 |  Porównanie prostokątów                                                    |
 |  Argumenty:                                                                |
 |      this -pierwszy składnik porównania                                    |
 |      v - drugi składnik porównania                                         |
 |  Zwraca:                                                                   |
 |      1 - jeżeli te prostokąty są takie same                                |
 |      0 - jeżeli te prostokąt są sobie różne                                |    
 */

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


/******************************************************************************
 |  Obrócenie prostokąta                                                      |
 |  Argumenty:                                                                |
 |      this - obracany prostokąt                                             |
 |      degrees - kąt obrotu prostokąta                                       |
 |      iterations - ile razy obrót ma zostać wykonany                        |
 |  Zwraca:                                                                   |
 |      Prostokąt po wykonaniu obrotów jako wskaźnik na parametr              |    
 */

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


/******************************************************************************
 |  Porównanie długości boków prostokąta                                      |
 |  Argumenty:                                                                |
 |      this - prostokąt                                                      |
 |  Zwraca:                                                                   |
 |      Nic ale wyświetli na standardowym wyjściu porównanie długości         |    
 |      boków prostokąta                                                      |
 */

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


/******************************************************************************
 |  Przesunięcie prostokąta o dany wektor                                     |
 |  Argumenty:                                                                |
 |      this - prostokąt                                                      |
 |      v - wektor                                                            |
 |  Zwraca:                                                                   |
 |      Prostokąt po przesunięciu jako wskaźnik na parametr                   |    
 */

Rectangle Rectangle::Move(Vector v){

  for(int i=0; i<4; i++){
    Points[i] = Points[i] + v;
  }

  return *this;
}


/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      rec - prostokąt.                                                      |
 */

std::ostream &operator<<(std::ostream &out, Rectangle const &rec){
  int i, j;
  for(i=0; i<4; i++){
    for(j=0; j<SIZE; j++){
      out << std::fixed << std::setprecision(10) << rec(i, j) << "\t";
    }
    out << std::endl;
  }
  i=0;
  for(j=0; j<SIZE; j++){
      out << std::fixed << std::setprecision(10) << rec(i, j) << "\t";
    }
    out << std::endl;
  return out;
}


/******************************************************************************
 |  Zapisz prostokąt do pliku                                                 |
 |  Argumenty:                                                                |
 |      Filename - nazwa pliku                                                |
 |      Rec - prostokąt.                                                      |
 |  Zwraca:                                                                   |
 |      1 - jeśli zapisanie odbędzie się pomyślnie                            |
 |      0 - jeśli nie                                                         |
 */

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