
#pragma once

#include "point.hpp"
#include "cluster.hpp"

#include <cstddef>
#include <cstdlib>
#include <vector>

namespace PKA {

// constructor
template <typename T> Cluster<T>::Cluster(const std::vector<T> &coord) {
  _coord = coord;
}

//
template <typename T> std::size_t Cluster<T>::GetSize() const {
  return _pointsId.size();
}

template <typename T> std::size_t Cluster<T>::GetDim() const {
  return _coord.size();
}

template <typename T> const std::vector<T> &Cluster<T>::GetCoord() const {
  return _coord;
}

template<typename T> void Cluster<T>::SetCoord(const std::vector<T> &coord){
   _coord = coord;
}

template <typename T> void Cluster<T>::Add(const std::size_t &pId) {
   _pointsId.push_back(pId);
}

template <typename T> const std::vector<std::size_t> &Cluster<T>::GetPointsId() const{
   return _pointsId;
}


template <typename T> void Cluster<T>::Clear() {
   _pointsId.clear();
}

} // namespace PKA

