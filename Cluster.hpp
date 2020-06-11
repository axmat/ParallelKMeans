#pragma once

#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <vector>

#include "Point.hpp"

namespace KM {

template <typename T> class Cluster {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point");

private:
  std::vector<std::size_t> _pointsId;

  std::vector<T> _coord;

public:
  Cluster();

  Cluster(const std::vector<T> &);

  ~Cluster();

  std::size_t GetSize() const;

  std::size_t GetDim() const;

  const std::vector<T> &GetCoord() const;

  void SetCoord(const std::vector<T> &);

  void Add(const std::size_t &);

  const std::vector<std::size_t> &GetPointsId() const;

  void Update(const std::vector<Point<T>> &);

  void Clear();
};

} // namespace KM
