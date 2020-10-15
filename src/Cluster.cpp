#include "../inc/Point.hpp"
#include "../inc/Cluster.hpp"

namespace KMeans {

template <typename T>
void Cluster<T>::Update(const std::vector<Point<T>> &data) {
   auto size = this->GetSize();
   auto dim = this->GetDim();
   auto pointsId = this->GetPointsId();
   std::vector<T> coord(dim, T(.0));
   for (auto &pointId : pointsId) {
      auto pCoord = data[pointId].GetCoord();
      for (std::size_t j = 0; j < dim; j++)
         coord[j] += pCoord[j];
   }
   for (std::size_t i = 0; i < dim; i++)
      coord[i] /= T(size);
   this->SetCoord(coord);
}

template class Cluster<float>;

template class Cluster<double>;

} // namespace KMeans
