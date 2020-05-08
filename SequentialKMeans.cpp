
#pragma once

#include <cstddef>
#include <limits>
#include <omp.h>
#include <random>
#include <numeric>
#include <vector>
#include <exception>

#include "Cluster.hpp"
#include "Point.hpp"
#include "SequentialKMeans.hpp"

namespace SeqKM {

using KM::Point;
using KM::Cluster;

static std::random_device rdev;
static std::mt19937_64 gen(rdev());

template <typename T>
auto initClusters(const std::vector<Point<T>> &data, const std::size_t &nClusters) {
  auto nData = data.size();
  std::uniform_int_distribution<std::size_t> unifIntDist(0, nData - 1);
  std::size_t nCluster = unifIntDist(gen);
  auto firstClusterCoord = data[nCluster].GetCoord();
  auto firstCluster = Cluster<T>(firstClusterCoord);
  std::vector<Cluster<T>> clusters( {firstCluster});
  auto inf = std::numeric_limits<T>::infinity();
  std::vector<T> minDist(nData, inf);
  std::vector<T> minPropDist(nData);
  for (std::size_t i = 0; i < nClusters; i++) {
    auto sum = T(.0);
    for (std::size_t i = 0; i < nData; i++) {
      T dist = sqEuclidianDist(data[i], clusters[nCluster]);
      if (dist < minDist[i])
        minDist[i] = dist; 
      sum += minDist[i];
    }
    for(std::size_t j=0;j<nData;j++)
       minPropDist[i] = minDist[i] / sum;
#ifdef DEBUG
   std::cout<<"min prop distance"<<std::endl;
   for(auto &x : minPropDist)
      std::cout<<x<<" ";
   std::endl;
#endif
    std::discrete_distribution<std::size_t> wUnifIntDist(minPropDist.begin(), minPropDist.end());
    nCluster = wUnifIntDist(gen);
    auto nextClusterCoord = data[nCluster].GetCoord();
    auto nextCluster = Cluster<T>(nextClusterCoord);
    clusters.push_back(nextCluster);
  }
#ifdef DEBUG
   std::cout<<"Clusters centers"<<std::endl;
   for(auto &C : clusters)
      std::cout<<"id : "<<C.GetClusterId()<<std::endl;
      std::cout<<"coord : "<<C.GetCoord()<<std::endl;
      std::cout<<"Points id :"<<std::endl;
      for(auto &id : C.GetPointsId)
         std::cout<<id<<std::endl;
   std::endl;
#endif
  return clusters;
}

// Squared Euclidian Distance.
template <typename T>
T sqEuclidianDist(const Point<T> &point, const Cluster<T> &cluster) {
   auto ndim = point.GetDim();
   auto &pointCoord = point.GetCoord();
   auto &clusterCoord = cluster.GetCoord();
   T dist = T(.0);
   for (std::size_t i = 0; i < ndim; i++){
      auto d = (pointCoord[i] - clusterCoord[i]);
      dist += d * d;
   }
  return dist;
}

// Assignment step
// return number of reassigned points
template<typename T>
std::size_t assignPoints(std::vector<Point<T>> &data, std::vector<Cluster<T>> &clusters){
   std::size_t nData = data.size();
   std::size_t nClusters = clusters.size();
   std::size_t nReasigned = 0;
   for(std::size_t i=0; i < nData; i++) {
      auto &P = data[i];
      T minDist = sqEuclidianDist(P, clusters[0]);
      std::size_t id = 0;
      for(std::size_t j = 0; j < nClusters; j++) {
         auto &C = clusters[j];
         T dist = sqEuclidianDist(P, C);
         if (dist < minDist){
            minDist = dist;
            id = j;
         }
      }
      if(P.GetClusterId() != id || !P.IsAssigned()){
         P.SetClusterId(id);
         clusters[id].Add(i);
         nReasigned++;
      }
   }
   return nReasigned;
}

// Update the clusters
template <typename T>
void updateClusters(const std::vector<Point<T>> &data, std::vector<Cluster<T>> &clusters) {
   std::size_t nClusters = clusters.size();
   for(std::size_t nCluster = 0; nCluster < nClusters; nCluster++){
      auto &C = clusters[nCluster];
      auto dim = C.GetDim();
      auto size = C.GetSize();
      auto pointsId = C.GetPointsId();
      std::vector<T> coord(dim, T(.0));
      for(std::size_t i=0; i<size ; i++){
         auto pointId = pointsId[i];
         auto &P = data[pointId];
         auto pCoord = P.GetCoord();
         for(std::size_t j=0; j<dim ; j++)
            coord[j] += pCoord[j];
      }
      for(std::size_t i = 0; i < dim ; i++)
         coord[i] /= T(size);
      C.SetCoord(coord);
      C.Clear();
   }
}

// Implementation of kmeans clustering algorithm
template <typename T>
std::vector<Cluster<T>>
kmeans(std::vector<Point<T>> &data, const std::size_t &nClusters, const std::size_t &iterMax, const T threshold) {
   auto clusters = initClusters(data, nClusters);
   std::size_t nData = data.size();
   std::size_t nIter = 0;
   std::size_t nReasigned = data.size();
   T fReasigned = T(1.0);
   while( nIter < iterMax && fReasigned> threshold) {
      nReasigned = assignPoints(data, clusters);
      updateClusters(data, clusters);
      fReasigned = nReasigned / nData;
      nIter++;
   }
   if(fReasigned > threshold)
      throw std::runtime_error("KMeans algorithm did not converge.");
   return clusters;
}

} // namespace SeqKM

