// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "matrix.hh"
#include "rectangle.hh"
#include "../include/lacze_do_gnuplota.hh"



int main() {
       double tmp1, tmp2;          /* Zmienne tymczasowe służące do odczytu parametrów od użytkownika */
       int tmp3; 
       char choice;                /* Wybór opcji przez użytkownika */
       double Tab[4][SIZE] = {{100.0, 100.0},{100.0, 200.0},{200.0, 200.0},{200.0, 100.0}};       /* Początkowe parametry prostokąta */
       Rectangle Rec(Tab);

       PzG::LaczeDoGNUPlota  Lacze;
       Lacze.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Ciagly,2);
       Lacze.ZmienTrybRys(PzG::TR_2D);
       Rec.CompareSides();
       
       while(choice!='k'){
              std::cout << std::endl << "o - obrot prostokata o zadany kat" << std::endl;
              std::cout << "p - przesuniecie prostokata o zadany wektor" << std::endl;
              std::cout << "w - wyswietlenie wspolrzednych wierzcholkow" << std::endl;
              std::cout << "m - wyswietl menu" << std::endl;
              std::cout << "k - koniec dzialania programu" << std::endl << std::endl;

              std::cout << "Twoj wybor? (m - menu) > ";

              std::cin >> choice;

              switch(choice){

                     case 'o':
                     std::cout << "Podaj wartosc kata obrotu w stopniach" << std::endl;
                     std::cin >> tmp1;
                     std::cout << std::endl << "Ile razy operacja obrotu ma byc powtorzona?" << std::endl;
                     std::cin >> tmp3;
                     Rec.Rotate(tmp1, tmp3);
                     Rec.CompareSides();
                     break;

                     case 'p':
                     {std::cout << "Wprowadz wspolrzedne wektora translacji w postaci dwoch liczb tzn. wspolrzednej x oraz wspolrzednej y." << std::endl;
                     std::cin >> tmp1 >> tmp2;
                     double VTab[SIZE] = {tmp1, tmp2};
                     Rec.Move(Vector(VTab));}
                     break;

                     case 'w':
                     std::cout << std::endl << Rec << std::endl;
                     if(!SaveRecToFile("../datasets/prostokat.dat", Rec)) return 1;
                     Lacze.Rysuj();
                     break;

                     case 'm':
                     break;

                     case 'k':
                     std::cout << "Koniec działania programu." << std::endl;
                     break;

                     default:
                     std::cout << "Nieprawidłowy wybór opcji" << std::endl;
                     break;
              }

       }

       return 1;

}
