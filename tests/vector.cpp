#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"
#include "../include/vector.hh"
#include <iostream>
#include <sstream>
#include <string>

TEST_CASE("Konstruktory"){

  Vector x;
  double Ty[SIZE] = {0,0};
  Vector y(Ty);

  CHECK(x == y);
}

TEST_CASE("Konstruktor parametryczny - vector"){

  double Tx[SIZE] = {0,2};

  Vector x(Tx);
  Vector y(x);

  CHECK(x == y);
}


TEST_CASE("Dodawanie"){

  double Tx[SIZE] = {1,2};
  double Ty[SIZE] = {3,-4};
  double Tz[SIZE] = {4, -2};

  Vector x(Tx), y(Ty), z(Tz);

  CHECK(x+y == z);
}


TEST_CASE("Odejmowanie"){

  double Tx[SIZE] = {1,2};
  double Ty[SIZE] = {3,-4};
  double Tz[SIZE] = {-2, 6};

  Vector x(Tx), y(Ty), z(Tz);

  CHECK(x-y == z);
}

TEST_CASE("Mnożenie vector * double"){

  double Tx[SIZE] = {1,2};
  double y = -2;
  double Tz[SIZE] = {-2,-4};

  Vector x(Tx), z(Tz);

  CHECK(x * y == z);
}

TEST_CASE("Dzielenie vector / double"){

  double Tx[SIZE] = {1,2};
  double y = -2;
  double Tz[SIZE] = {-0.5,-1};

  Vector x(Tx), z(Tz);

  CHECK(x / y == z);
}

TEST_CASE("Dzielenie vector / zero"){

  double Tx[SIZE] = {1,2};
  double y = 0;

  Vector x(Tx);

  WARN_THROWS(x / y);
}

TEST_CASE("Przypisanie"){

  double Tx[SIZE] = {1,2};
  Vector x(Tx), y;

  y = x;

  CHECK(y == x);
}

TEST_CASE("Operator []"){

  double Tx[SIZE] = {-2,0};
  Vector x(Tx);

  CHECK( x[0] == -2);
}

TEST_CASE("Operator [] - poza zasięgiem na plus"){

  double Tx[SIZE] = {-2,0};
  Vector x(Tx);

  WARN_THROWS(x[SIZE]);
}

TEST_CASE("Operator [] - poza zasięgiem na minus"){

  double Tx[SIZE] = {-2,0};
  Vector x(Tx);

  WARN_THROWS(x[-1]);
}

TEST_CASE("Porownanie - minimalnie nierowne"){
  
  double Tx[SIZE] = {1,1};
  double Ty[SIZE] = {1.01,1};

  Vector x(Tx), y(Ty);

  CHECK(!(x == y));
}

TEST_CASE("Porownanie - minimalnie rowne"){
  
  double Tx[SIZE] = {1,1};
  double Ty[SIZE] = {1.009,1};

  Vector x(Tx), y(Ty);

  CHECK(x == y);
}

TEST_CASE("Odległość między wektorami"){

  double Tx[SIZE] = {1,1};
  double Ty[SIZE] = {-2, 5};

  Vector x(Tx), y(Ty);

  CHECK(Distance(x, y) == 5);
}

TEST_CASE("Odległość między wektorami - zero"){

  double Tx[SIZE] = {1,1};

  Vector x(Tx), y(Tx);

  CHECK(Distance(x, y) == 0);
}

TEST_CASE("Wyświetlanie"){

  double Tx[SIZE] = {5,2};
  Vector x(Tx);

  std::stringstream out;

  out << x;

  CHECK("[ 5.00000 ]\n[ 2.00000 ]\n" == out.str());
}

TEST_CASE("Wczytywanie"){

  std::stringstream in("2 \n 3");
  double Ty[SIZE] = {2,3};
  Vector x, y(Ty);

  in >> x;

  CHECK(x ==y);
}
