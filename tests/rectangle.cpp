#include "../tests/doctest/doctest.h"
#include "../include/rectangle.hh"
#include <iostream>
#include <sstream>
#include <string>

TEST_CASE("Konstruktory"){

  Rectangle x;
  double Ty[4][SIZE] = {{0,1},{0,0},{0,0},{0,0}};
  Rectangle y(Ty);

  CHECK(x == y);
}

TEST_CASE("Konstruktor parametryczny - rectangle"){

  double Ty[4][SIZE] = {{4,5},{-7,0},{4,5},{-7,0}};
  Rectangle y(Ty);
  Rectangle x(y);

  CHECK(x == y);
}

TEST_CASE("Obrót 0 stopni 10 razy"){

  double Tx[4][SIZE] = {{1,1},{1,2},{2,2},{2,1}};
  Rectangle x(Tx), y(x);

  x.Rotate(0, 10);

  CHECK(x == y);
}

TEST_CASE("Obrót 90 stopni"){

  double Tx[4][SIZE] = {{1,1},{1,2},{2,2},{2,1}};
  double Ty[4][SIZE] = {{-1,1},{-2,1},{-2,2},{-1,2}};
  Rectangle x(Tx), y(Ty);

  x.Rotate(90, 1);

  CHECK(x == y);
}

TEST_CASE("Obrót -90 stopni"){

  double Tx[4][SIZE] = {{1,1},{1,2},{2,2},{2,1}};
  double Ty[4][SIZE] = {{1,-1},{2,-1},{2,-2},{1,-2}};
  Rectangle x(Tx), y(Ty);

  x.Rotate(-90, 1);

  CHECK(x == y);
}

TEST_CASE("Przesuniecie [0,0]"){

  double Tx[4][SIZE] = {{1,1},{1,2},{2,2},{2,1}};
  Rectangle x(Tx), y(x);
  Vector v;
  
  x.Move(v);

  CHECK(x == y);
}

TEST_CASE("Przesuniecie [1,2]"){

  double Tx[4][SIZE] = {{1,1},{1,2},{2,2},{2,1}};
  double Ty[4][SIZE] = {{2,3},{2,4},{3,4},{3,3}};
  Rectangle x(Tx), y(Ty);
  double Tv[SIZE] = {1,2};
  Vector v(Tv);

  x.Move(v);

  CHECK(x == y);
}

TEST_CASE("Wyświetlanie"){

  double Tx[4][SIZE] = {{1,1},{1,2},{2,2},{2,1}};
  Rectangle x(Tx);

  std::stringstream out;

  out << x;

  CHECK("1.0000000000\t1.0000000000\t\n1.0000000000\t2.0000000000\t\n2.0000000000\t2.0000000000\t\n2.0000000000\t1.0000000000\t\n1.0000000000\t1.0000000000\t\n"
  == out.str());
}


