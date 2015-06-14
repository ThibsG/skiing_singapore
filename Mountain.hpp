#ifndef MOUNTAIN_HPP
#define MOUNTAIN_HPP

#include <string>
#include <vector>
#include <list>

namespace SkiMountain
{

class Viewer;

/**
 * @class Mountain
 * Class representation of the mountain
 */
class Mountain
{
  friend class Viewer;
  public:
    /**
     * @struct Number
     * Number is an element of the mountain.
     * It is built from position (row,col) and a value
     */
    struct Number {
      uint16_t row;
      uint16_t col;
      uint16_t value;

      Number(uint16_t r, uint16_t c, uint16_t v);
      bool operator==(const Number& n) const;
    };

    Mountain();
    bool load(const std::string& filename);

    inline uint16_t cols() const;
    inline uint16_t rows() const;

    std::list<Number> neighbors(uint16_t row, uint16_t col) const;
    Number numberAt(uint16_t row, uint16_t col) const;

    void clear();

  private:
    std::vector<std::vector<uint16_t>> m_elements;
    uint16_t m_cols;
    uint16_t m_rows;

    uint16_t valueAt(uint16_t row, uint16_t col) const;
};

uint16_t Mountain::cols() const
{
  return m_cols;
}

uint16_t Mountain::rows() const
{
  return m_rows;
}

}

#endif