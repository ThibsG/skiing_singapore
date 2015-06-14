#include "Skiing.hpp"

#include <algorithm>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

namespace SkiMountain
{

/**
 * @struct Cache
 * Cache structure to store already explored neighbors
 */
struct Cache
{
  bool isVisited;
  Path longestPath;

  Cache() :
    isVisited(false)
  {}
};

void Skiing::solve(const Mountain& mountain)
{
  m_longestPath.clear();

  vector<vector<Cache>> cache(mountain.rows());
  for(auto& line : cache)
    line.resize(mountain.cols());

  for(uint16_t row = 0 ; row < mountain.rows() ; ++row)
  {
    for(uint16_t col = 0 ; col < mountain.cols() ; ++col)
    {
      Path pathFound = discover(mountain, cache, mountain.numberAt(row, col));

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

Path Skiing::discover(const Mountain& mountain, vector<vector<Cache>>& cache, const Mountain::Number& origin)
{
  auto neighbors = mountain.neighbors(origin);

  // Stop condition (no valid neighbors)
  if(neighbors.empty())
    return Path(1, origin.value);

  // Valid neighbors exploration
  Path best;
  for(const auto& neighbor : neighbors)
  {
    Cache& c = cache[neighbor.row][neighbor.col];
    if(not c.isVisited)
    {
      // Recursive call
      c.longestPath = discover(mountain, cache, neighbor);
      c.isVisited = true;
    }

    if(c.longestPath.size() > best.size())
      best = c.longestPath;
  }

  best.insert(best.begin(), origin.value);
  return best;
}

}