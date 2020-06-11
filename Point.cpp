
#include <cstddef>
#include <type_traits>
#include <vector>

#include "Point.hpp"

namespace KM {

template <typename T> Point<T>::Point() { _assigned = false; }

template <typename T> Point<T>::Point(const std::vector<T> &coord) {
  _coord = coord;
  _assigned = false;
}

template <typename T> Point<T>::~Point() {}

template <typename T> std::size_t Point<T>::GetDim() const {
  return _coord.size();
}

template <typename T> const std::vector<T> &Point<T>::GetCoord() const {
  return _coord;
}

template <typename T> void Point<T>::SetCoord(const std::vector<T> &coord) {
  _coord = coord;
}

template <typename T> const std::size_t &Point<T>::GetClusterId() const {
  return _clusterId;
}

template <typename T> void Point<T>::SetClusterId(const std::size_t &id) {
  _clusterId = id;
  _assigned = true;
}

template <typename T> bool Point<T>::IsAssigned() const { return _assigned; }

template class Point<float>;
template class Point<double>;

} // namespace KM
