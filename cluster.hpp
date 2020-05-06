

#pragma once
#include "point.hpp"
#include <cstddef> //std::size_t
#include <cstdlib>
#include <vector>

namespace PKA {

template <typename T>
class Cluster {
  static_assert(std::is_floating_point<T>::value, "T must be a floating point");
private:
  std::vector<std::size_t> _pointsId;
  std::vector<T> _coord;
public:
  Cluster(const std::vector<T> &);

  ~Cluster(){};

  std::size_t GetSize() const;

  std::size_t GetDim() const;

  const std::vector<T> &GetCoord() const;

  void SetCoord(const std::vector<T> &);

  void Add(const std::size_t &);

  const std::vector<std::size_t> &GetPointsId() const;

  void Clear();

  //void Update();
};

//------------------------------ Class Point Implementation
//------------------------------

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
