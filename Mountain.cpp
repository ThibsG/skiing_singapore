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

Mountain::Number::Number(uint16_t r, uint16_t c) :
  Mountain::Number(r, c, 0)
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

list<Mountain::Number> Mountain::neighbors(const Mountain::Number& origine) const
{
  list<Number> neighborhood;

  auto row = origine.row;
  auto col = origine.col;
  auto val = origine.value;

  if(row >= m_rows || col >= m_cols)
    return neighborhood;

  Mountain::Number number(row - 1, col);

  // North
  if(row > 0)
  {
    number.value = m_elements[row - 1][col];
    if(number.value < val)
      neighborhood.push_back(number);
  }

  // South
  if(row < (m_rows - 1))
  {
    number.row = row + 1;
    number.value = m_elements[row + 1][col];
    if(number.value < val)
      neighborhood.push_back(number);
  }

  number.row = row;
  number.col = col - 1;

  // West
  if(col > 0)
  {
    number.value = m_elements[row][col - 1];
    if(number.value < val)
      neighborhood.push_back(number);
  }

  // East
  if(col < (m_cols - 1))
  {
    number.col = col + 1;
    number.value = m_elements[row][col + 1];
    if(number.value < val)
      neighborhood.push_back(number);
  }

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