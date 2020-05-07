
#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>

namespace KM {

template <typename T> class Point {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point");

private:
  // coordinat of a point
  std::vector<T> _coord;
  // cluster id
  std::size_t _clusterId;

  bool _assigned;

public:
  Point(const std::vector<T> &);

  ~Point(){};

  std::size_t GetDim() const;

  const std::vector<T> &GetCoord() const;

  void SetCoord(const std::vector<T> &);

  const std::size_t &GetClusterId() const;

  void SetClusterId(const std::size_t &);

  bool IsAssigned() const;
};


} // namespace PKA
