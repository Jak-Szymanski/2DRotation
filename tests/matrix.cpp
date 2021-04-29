#include "../tests/doctest/doctest.h"
#include "../include/matrix.hh"
#include <iostream>
#include <sstream>
#include <string>

TEST_CASE("Konstruktory"){

  Matrix x;
  double Ty[SIZE][SIZE] = {{0,0},{0,0}};
  Matrix y(Ty);

  CHECK(x == y);
}

TEST_CASE("Konstruktor parametryczny - matrix"){

  double Ty[SIZE][SIZE] = {{4,5},{-7,0}};
  Matrix y(Ty);
  Matrix x(y);

  CHECK(x == y);
}

TEST_CASE("Dodawanie"){

  double Tx[SIZE][SIZE] = {{1.5,-1},{5,0}};
  double Ty[SIZE][SIZE] = {{-0.5,-3},{2,-1}};
  double Tz[SIZE][SIZE] = {{1,-4},{7,-1}};
  Matrix x(Tx), y(Ty), z(Tz);

  CHECK(z == x + y);
}

TEST_CASE("Mnożenie matrix * vector"){

  double Tv[SIZE] = {1,2};
  double Tm[SIZE][SIZE] = {{0,-1},{4,2}};
  double Tr[SIZE] = {-2,8};
  Vector v(Tv), r(Tr);
  Matrix m(Tm);

  CHECK(r == m * v);
}

TEST_CASE("Operator ()"){

  double Tx[SIZE][SIZE] = {{4,5},{-7,0}};
  Matrix x(Tx);

  CHECK(x(1, 0) == -7);
}

TEST_CASE("Operator () - wiersz poza zasięgiem na plus"){

  double Tx[SIZE][SIZE] = {{4,5},{-7,0}};
  Matrix x(Tx);

  WARN_THROWS(x(SIZE, 0));
}

TEST_CASE("Operator () - wiersz poza zasięgiem na minus"){

  double Tx[SIZE][SIZE] = {{4,5},{-7,0}};
  Matrix x(Tx);

  WARN_THROWS(x(-1, 0));
}

TEST_CASE("Operator () - kolumna poza zasięgiem na plus"){

  double Tx[SIZE][SIZE] = {{4,5},{-7,0}};
  Matrix x(Tx);

  WARN_THROWS(x(1, SIZE));
}

TEST_CASE("Operator () - kolumna poza zasięgiem na minus"){

  double Tx[SIZE][SIZE] = {{4,5},{-7,0}};
  Matrix x(Tx);

  WARN_THROWS(x(1, -1));
}

TEST_CASE("Porownanie - minimalnie nierowne"){
  
  double Tx[SIZE][SIZE] = {{1,1},{1,1}};
  double Ty[SIZE][SIZE] = {{1,1},{1.01,1}};

  Matrix x(Tx), y(Ty);

  CHECK(!(x == y));
}

TEST_CASE("Porownanie - minimalnie rowne"){
  
  double Tx[SIZE][SIZE] = {{1,1},{1,1}};
  double Ty[SIZE][SIZE] = {{1,1},{1.009,1}};

  Matrix x(Tx), y(Ty);

  CHECK(x == y);
}

TEST_CASE("Macierz obrotu 0 stopni"){

  double a = 0;
  double Tx[SIZE][SIZE] = {{1,0},{0,1}};
  Matrix x(Tx);
  Matrix y;
  y.Rotation(a);

  CHECK(x == y);
}

TEST_CASE("Macierz obrotu 90 stopni"){

  double a = 90;
  double Tx[SIZE][SIZE] = {{0,-1},{1,0}};
  Matrix x(Tx);
  Matrix y;
  y.Rotation(a);

  CHECK(x == y);
}

TEST_CASE("Obliczanie wyznacznika metodą Gaussa - przykładowa macierz"){

  double Tx[SIZE][SIZE] = {{1, -2},{-4, 5}};
  Matrix x(Tx);

  double det = x.detGauss();

  CHECK(det == -3);
}

TEST_CASE("Obliczanie wyznacznika metodą Gaussa - błąd"){

  double Tx[SIZE][SIZE] = {{0, -2},{-4, 5}};
  Matrix x(Tx);

  WARN_THROWS(x.detGauss());
}

TEST_CASE("Wyświetlanie"){

  double Tx[SIZE][SIZE] = {{5,2},{1,0}};
  Matrix x(Tx);

  std::stringstream out;

  out << x;

  CHECK("| 5.00000 | | 2.00000 | \n| 1.00000 | | 0.00000 | \n" == out.str());
}

TEST_CASE("Wczytywanie"){

  std::stringstream in("2 \n 3 \n 0.77 \n 0");
  double Ty[SIZE][SIZE] = {{2,3},{0.77,0}};
  Matrix x, y(Ty);

  in >> x;

  CHECK(x == y);
}


