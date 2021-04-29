
#include "../include/size.hh"
#include "../include/vector.hh"
#include <iomanip> 
#include <fstream> 

#define MIN_DIFF  0.01

/******************************************************************************
 |  Konstruktor klasy Vector.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartoscia 0.                                       |
 */
Vector::Vector() {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = 0;
    }
}


/******************************************************************************
 |  Konstruktor parametryczny klasy Vector.                                   |
 |  Argumenty:                                                                |
 |      tmp - Jednowymiarowa tablica typu double.                             |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartosciami podanymi w argumencie.                 |
 */

Vector::Vector(double tmp[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = tmp[i];
    }
}


/******************************************************************************
 |  Konstruktor parametryczny klasy Vector.                                   |
 |  Argumenty:                                                                |
 |      v - Wektor                                                            |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartosciami podanymi w argumencie.                 |
 */

Vector::Vector(const Vector &v){
    for (int i = 0; i < SIZE; ++i){
        size[i] = v[i];
    }
}


/******************************************************************************
 |  Realizuje dodawanie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik dodawania,                                   |
 |      v - drugi skladnik dodawania.                                         |
 |  Zwraca:                                                                   |
 |      Sume dwoch skladnikow przekazanych jako wskaznik                      |
 |      na parametr.                                                          |
 */
Vector Vector::operator + (const Vector &v) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] += v[i];
    }
    return result;
}


/******************************************************************************
 |  Realizuje odejmowanie dwoch wektorow.                                     |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik odejmowania,                                 |
 |      v - drugi skladnik odejmowania.                                       |
 |  Zwraca:                                                                   |
 |      Roznice dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */
Vector Vector::operator - (const Vector &v) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] -= v[i];
    }
    return result;
}


/******************************************************************************
 |  Realizuje mnozenie wektora przez liczbe zmiennoprzecinkowa.               |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik mnozenia (wektor),                           |
 |      v - drugi skladnik mnozenia (liczba typu double).                     |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */

Vector Vector::operator * (const double &tmp) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] *= tmp;
    }
    return result;
}


/******************************************************************************
 |  Realizuje dzielenie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - licznik dzielenia,                                             |
 |      v - mianownik dzielenia.                                              |
 |  Zwraca:                                                                   |
 |      Iloraz dwoch skladnikow przekazanych jako wskaznik                    |
 |      na parametr.                                                          |
 */

Vector Vector::operator / (const double &tmp) {
    Vector result;

    if (tmp == 0){
        throw std::runtime_error("Błąd - dzielenie przez zero \n");
    }
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] / tmp;
    }

    return result;
}

/******************************************************************************
 |  Realizuje przypisanie wartości jednego wektora do drugiego                |
 |  Argumenty:                                                                |
 |      this - wektor do którego wartość będzie wpisana,                      |
 |      v - wektor z którego wartość będzie przypisana,                       |
 |  Zwraca:                                                                   |
 |      Gotowy wektor po przypisaniu jako wskaznik                            |
 |      na parametr                                                           | 
 */

Vector Vector::operator = (const Vector &v){
    for (int i = 0; i < SIZE; ++i){
        size[i] = v[i];
    }
    return *this;
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy jako stala.                   |
 */

const double &Vector::operator [] (int index) const {
    if (index < 0 || index >= SIZE) {
        throw std::runtime_error("Error: Wektor jest poza zasiegiem! \n");
    } 
    return size[index];
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy.                              |
 */

double &Vector::operator[](int index) {
    return const_cast<double &>(const_cast<const Vector *>(this)->operator[](index));
}


/******************************************************************************
 |  Porównanie wektorów                                                       |
 |  Argumenty:                                                                |
 |      this -pierwszy składnik porównania                                    |
 |      v - drugi składnik porównania                                         |
 |  Zwraca:                                                                   |
 |      1 - jeżeli te wektory są takie same                                   |
 |      0 - jeżeli te wektory są sobie różne                                  |    
 */

bool Vector::operator == (const Vector &v) const{
    for (int i = 0; i < SIZE; ++i){
        if(abs(size[i] - v[i]) > MIN_DIFF){
            return 0;
        }
    }
    return 1;    
}


/******************************************************************************
 |  Obliczanie odległości między dwoma punktami (wektorami)                   |
 |  Argumenty:                                                                |
 |      v1 - pierwszy punkt (wektor)                                          |
 |      v2 - drugi punkt (wektor)                                             |
 |  Zwraca:                                                                   |
 |      Odległośc między tymi dwoma punktami jako double                      |
 */

double Distance (const Vector v1, const Vector v2){

    double result = 0;

    for (int i = 0; i < SIZE; ++i){
        result += pow((v1[i] - v2[i]),2);
    }
    result = sqrt(result);
    return result; 
}



/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      tmp - wektor.                                                         |
 */
std::ostream &operator << (std::ostream &out, Vector const &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        out << std::fixed << std::setprecision(5) << "[ " << tmp[i] << " ]\n";
    }
    return out;
}


/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      tmp - wektor.                                                         |
 */
std::istream &operator >> (std::istream &in, Vector &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}