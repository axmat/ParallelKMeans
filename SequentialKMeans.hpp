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

namespace KM {

// Initialize centers using kmeans++ algorithm
template <typename T>
auto SeqInitClusters(const std::vector<Point<T>>& data, const std::size_t& nClusters);

// Squared Euclidian Distance
template <typename T>
T SeqSqEuclidianDist(const Point<T>& point, const Cluster<T>& cluster);

// Assignment step
template<typename T>
std::size_t SeqAssignPoints(std::vector<Point<T>>& data, std::vector<Cluster<T>>& clusters);

// Update the clusters
template <typename T>
void SeqUpdateClusters(const std::vector<Point<T>>& data, std::vector<Cluster<T>>& clusters);

// Implementation of sequential kmeans clustering algorithm
template <typename T>
std::vector<Cluster<T>>
SeqKMeans(std::vector<Point<T>>& data, const std::size_t& nClusters, const std::size_t& iterMax = 10'000, const T threshold = 0.01);

} // namespace KM

