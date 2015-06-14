#include <iostream>
#include <chrono>

#include "Mountain.hpp"
#include "Skiing.hpp"

using namespace SkiMountain;
using namespace std;

namespace SkiMountain
{

class Viewer
{
  public:
    static void show(const Mountain& m)
    {
      cout << " ++ Affichage du contenu ++ " << endl;
      cout << " -  Matrice de " << m.rows() << "x" << m.cols() << endl;
      for(auto cols : m.m_elements) {
        for(auto rows : cols)
          cout << rows << " ";
        cout << endl;
      };
    }

    static void best(const Skiing& s)
    {
      for(auto elt : s.longestPath())
        cout << elt << " ";
      cout << endl;
    }
};

}

void printTiming(const string& pre, const chrono::system_clock::time_point& t1, const chrono::system_clock::time_point& t2);
bool tests();

int main()
{
  cout << "Challenge skiing in Singapour" << endl;

  if(not tests()) {
    cout << "Tests failed" << endl;
    return EXIT_FAILURE;
  }

  Mountain mountain;

  auto t1 = chrono::system_clock::now();
  mountain.load("../map_simple.txt");
  auto t2 = chrono::system_clock::now();
  printTiming("Loaded map_simple.txt", t1, t2);

//   Viewer::show(mountain);

  Skiing skiing;

  t1 = chrono::system_clock::now();
  skiing.solve(mountain);
  t2 = chrono::system_clock::now();
  printTiming("Solved map_simple.txt", t1, t2);

  cout << "Longest path found is : ";
  Viewer::best(skiing);

  t1 = chrono::system_clock::now();
  mountain.load("../map_1000.txt");
  t2 = chrono::system_clock::now();
  printTiming("Loaded map_1000.txt", t1, t2);

  t1 = chrono::system_clock::now();
  skiing.solve(mountain);
  t2 = chrono::system_clock::now();
  printTiming("Solved map_1000.txt", t1, t2);

  cout << "Longest path found is : ";
  Viewer::best(skiing);

  return EXIT_SUCCESS;
}

void printTiming(const string& pre, const chrono::_V2::system_clock::time_point& t1, const chrono::_V2::system_clock::time_point& t2)
{
  chrono::duration<double, milli> nbrMilliSecondes = (t2 - t1);
  cout << pre << " in " << nbrMilliSecondes.count() << " ms" << endl;
}

bool tests()
{
  Mountain mountain;
  mountain.load("../map_simple.txt");

  auto number = mountain.numberAt(1,2);
  if(number.value != 9)
    return false;

  auto neighbors = mountain.neighbors(1, 2);
  if(neighbors.size() != 4)
    return false;

  int i = 0;
  for(auto number : neighbors) {
    if((i == 0 && number.value != 7) ||
       (i == 1 && number.value != 2) ||
       (i == 2 && number.value != 5) ||
       (i == 3 && number.value != 3))
      return false;
    ++i;
  }

  return true;
}