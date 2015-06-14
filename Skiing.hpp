#ifndef SKIING_HPP
#define SKIING_HPP

#include "Mountain.hpp"

#include <list>

namespace SkiMountain
{

/// Path representation
typedef std::vector<uint16_t> Path;

/**
 * @class Skiing
 * Challenge solver.
 * Used to help you skiing over the mountain
 */
class Skiing
{
  public:
    void solve(const Mountain& moutain);

    inline uint16_t longestDrop() const;
    inline const Path& longestPath() const;

  private:
    Path m_longestPath;

    Path discover(const Mountain& mountain, const Mountain::Number& origine);
};

uint16_t Skiing::longestDrop() const
{
  return m_longestPath.front() - m_longestPath.back();
}

const Path& Skiing::longestPath() const
{
  return m_longestPath;
}

}

#endif