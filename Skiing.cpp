#include "Skiing.hpp"

#include <algorithm>
#include <vector>
#include <list>

using namespace std;

namespace SkiMountain
{

void Skiing::solve(const Mountain& mountain)
{
  m_longestPath.clear();

  for(uint16_t row = 0 ; row < mountain.rows() ; ++row)
  {
    for(uint16_t col = 0 ; col < mountain.cols() ; ++col)
    {
      Path pathFound = discover(mountain, mountain.numberAt(row, col));

      if(pathFound.size() > m_longestPath.size())
      {
        m_longestPath = pathFound;
      }
      else if(pathFound.size() == m_longestPath.size())
      {
        auto newDrop = pathFound.front() - pathFound.back();
        if(newDrop > longestDrop())
          m_longestPath = pathFound;
      }
    }
  }
}

Path Skiing::discover(const Mountain& mountain, const Mountain::Number& origine)
{
  auto neighbors = mountain.neighbors(origine.row, origine.col);

  // Non-valid neighbors removal
  neighbors.erase(remove_if(neighbors.begin(), neighbors.end(), [=](const Mountain::Number& neighbor) {
    return (neighbor.value >= origine.value) or (neighbor == origine);
  }), neighbors.end());

  Path path;
  path.push_back(origine.value);

  // Stop condition (no valid neighbors)
  if(neighbors.empty())
    return path;

  // Valid neighbors exploration
  Path best;
  for(auto neighbor : neighbors)
  {
    // Recursive call
    Path p = discover(mountain, neighbor);

    if(p.size() > best.size())
      best = p;
  }

  path.insert(path.end(), best.begin(), best.end());
  return path;
}



}