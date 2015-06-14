#include "Mountain.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

namespace SkiMountain
{

Mountain::Number::Number(uint16_t r, uint16_t c, uint16_t v) :
  row(r),
  col(c),
  value(v)
{}

bool Mountain::Number::operator==(const Number& n) const
{
  return (row == n.row) && (col == n.col);
}

Mountain::Mountain() :
  m_cols(0),
  m_rows(0)
{
}

void Mountain::clear()
{
  m_cols = 0;
  m_rows = 0;
  m_elements.clear();
}

bool Mountain::load(const string& filename)
{
  clear();

  ifstream ifs(filename);
  if(not ifs) {
    cout << "Cannot open file : " << filename << endl;
    return false;
  }

  ifs >> m_rows >> m_cols;

  // Lecture de la matrice
  m_elements.resize(m_rows);
  for(auto& line : m_elements)
  {
    line.resize(m_cols);
    for(auto& elt : line)
      ifs >> elt;
  }

  return true;
}

list<Mountain::Number> Mountain::neighbors(uint16_t row, uint16_t col) const
{
  list<Number> neighborhood;

  if(row >= m_rows || col >= m_cols)
    return neighborhood;

  if(row > 0)
    neighborhood.push_back(numberAt(row - 1, col));
  if(row < (m_rows - 1))
    neighborhood.push_back(numberAt(row + 1, col));
  if(col > 0)
    neighborhood.push_back(numberAt(row,     col - 1));
  if(col < (m_cols - 1))
    neighborhood.push_back(numberAt(row,     col + 1));
  return neighborhood;
}

Mountain::Number Mountain::numberAt(uint16_t row, uint16_t col) const
{
  return Number(row, col, valueAt(row, col));
}

uint16_t Mountain::valueAt(uint16_t row, uint16_t col) const
{
  return m_elements[row][col];
}

}