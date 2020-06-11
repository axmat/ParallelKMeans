#include <cstddef>
#include <cstdlib>
#include <vector>

#include "Point.hpp"

#include "Cluster.hpp"

namespace KM {

template <typename T> Cluster<T>::Cluster() {}

template <typename T> Cluster<T>::Cluster(const std::vector<T> &coord) {
  _coord = coord;
}

template <typename T> Cluster<T>::~Cluster() {}

template <typename T> std::size_t Cluster<T>::GetSize() const {
  return _pointsId.size();
}

template <typename T> std::size_t Cluster<T>::GetDim() const {
  return _coord.size();
}

template <typename T> const std::vector<T> &Cluster<T>::GetCoord() const {
  return _coord;
}

template <typename T> void Cluster<T>::SetCoord(const std::vector<T> &coord) {
  _coord = coord;
}

template <typename T> void Cluster<T>::Add(const std::size_t &pId) {
  _pointsId.push_back(pId);
}

template <typename T>
const std::vector<std::size_t> &Cluster<T>::GetPointsId() const {
  return _pointsId;
}

template <typename T>
void Cluster<T>::Update(const std::vector<Point<T>> &data) {
  auto size = this->GetSize();
  auto dim = this->GetDim();
  auto pointsId = this->GetPointsId();
  std::vector<T> coord(dim, T(.0));
  for(auto &pointId : pointsId){
     auto pCoord = data[pointId].GetCoord();
     for (std::size_t j = 0; j < dim; j++)
      coord[j] += pCoord[j];
  }
  for (std::size_t i = 0; i < dim; i++)
    coord[i] /= T(size);
  this->SetCoord(coord);
}

template <typename T> void Cluster<T>::Clear() { _pointsId.clear(); }

template class Cluster<float>;

template class Cluster<double>;

} // namespace KM
