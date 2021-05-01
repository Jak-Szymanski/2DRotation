
#include "../include/size.hh"
#include "../include/vector.hh"
#include "../include/matrix.hh"
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <cmath>

#define PI 3.14159265358979323846 
#define MIN_DIFF  0.01

/******************************************************************************
 |  Konstruktor klasy Matrix.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Macierz wypelnione wartoscia 0.                                       |
 */
Matrix::Matrix() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = 0;
        }
    }
}


/******************************************************************************
 |  Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
 */
Matrix::Matrix(double tmp[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = tmp[i][j];
        }
    }
}


/******************************************************************************
 |  Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      mat - Macierz                                                         |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
 */

Matrix::Matrix(const Matrix &mat){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = mat(i, j);
        }
    }    
}


/******************************************************************************
 |  Przeciążenie dodawania macierzy                                           |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik dodawania,                                   |
 |      tmp - drugi skladnik dodawania.                                       |
 |  Zwraca:                                                                   |
 |      Macierz - iloczyn dwóch podanych macierzy.                            |
 */

Matrix Matrix::operator + (Matrix tmp) {
    Matrix result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}


/******************************************************************************
 |  Realizuje mnozenie macierzy przez wektor.                                 |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik mnozenia,                     |
 |      tmp - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wektor.                    |
 */

Vector Matrix::operator * (Vector tmp) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}


/******************************************************************************
 |  Realizuje mnozenie macierzy przez macierz.                                |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik mnozenia,                                    |
 |      tmp - drugi skladnik mnozenia.                                        |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako macierz.                   |
 */

Matrix Matrix::operator * (Matrix tmp)  {
    Matrix result;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            for (int k = 0; k < SIZE; ++k){
                result.value[i][j] += value[i][k] * tmp.value[k][j]; 
            }   
        }
    }

    return result;
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy.                             |
 */

double &Matrix::operator()(unsigned int row, unsigned int column) {

    if (row >= SIZE) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return value[row][column];
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
const double &Matrix::operator () (unsigned int row, unsigned int column) const {

    if (row >= SIZE) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    if (column >= SIZE) {
        throw std::runtime_error("Error: Macierz jest poza zasiegiem \n");
    }

    return value[row][column];
}


/******************************************************************************
 |  Porównanie macierzy                                                       |
 |  Argumenty:                                                                |
 |      this -pierwszy składnik porównania                                    |
 |      mat - drugi składnik porównania                                         |
 |  Zwraca:                                                                   |
 |      1 - jeżeli te macierze są takie same                                  |
 |      0 - jeżeli te macierze są sobie różne                                 |    
 */

bool Matrix::operator == (const Matrix &mat) const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if(abs(value[i][j] - mat(i, j)) >= MIN_DIFF){
                return 0;
            }
        }
    }
    return 1;
}


/******************************************************************************
 |  Wyznaczanie macierzy obrotu                                               |
 |  Argumenty:                                                                |
 |      this - zwracana macierz                                               |
 |      degrees - kąt w stopniach                                             |
 |  Zwraca:                                                                   |
 |      Macierz obrotu o dany kąt jako wskaźnik na parametr                   |  
 */

Matrix Matrix::Rotation(double degrees){
    double radians = degrees * (PI /180);
    this->value[0][0] = this->value[1][1] = cos(radians);
    this->value[0][1] = -sin(radians);
    this->value[1][0] = sin(radians);

    return *this;
}


/******************************************************************************
 |  Obliczanie wyznacznika macierzy metodą eliminacji Gaussa                  |
 |  Argumenty:                                                                |
 |      this - dana macierz                                                   |
 |  Zwraca:                                                                   |
 |      Wartość wyznacznika podanej macierzy jako double                      |
 |   UWAGA :                                                                  |
 |      Ta metoda nie działa jeżeli któraś z komórek na głównej przekątnej    |
 |      ma wartość 0                                                          |
 */

double Matrix::detGauss(){
    double ratio, det=1;
    int i,j,k;
    j = 0;
    for(i=0;i<=SIZE-2;i++)
        {
            if(value[i][j] == 0.0)
            {
                throw std::runtime_error("Danej macierzy nie można policzyć tą metodą \n");
            }
            for(j=i+1;j<=SIZE-1;j++)
            {
                ratio = value[j][i]/value[i][i];

                for(k=0;k<=SIZE-1;k++)
                {
                        value[j][k] -= ratio * value[i][k];
                }
            }
        }

    for(i=0;i<=SIZE-1;i++){
        det *= value[i][i];
    }

    return det;
}


/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                         |
 */

std::istream &operator>>(std::istream &in, Matrix &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}


/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      mat - macierz.                                                        |
 */

std::ostream &operator<<(std::ostream &out, const Matrix &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            out << std::fixed << std::setprecision(5) <<"| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        out << std::endl;
    }
    return out;
}
