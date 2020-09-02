#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Point.hpp"
#include "Cluster.hpp"
#include "CSV.hpp"
#include "SequentialKMeans.hpp"
#include "ParallelKMeans.hpp"

#include <omp.h>


int main(int argc, char *argv[]) {
   if (argc != 6){
      std::cout << "+-------------------------------------------------------+" << std::endl;
      std::cout << "| Usage: ./benchmark  K num_threads N iterMax threshold |" << std::endl;
      std::cout << "+-------------------------------------------------------+" << std::endl;
      return 1;
   }

   std::size_t K = ::atof(argv[1]);
   int num_threads = ::atof(argv[2]);
   std::size_t N = ::atof(argv[3]);
   std::size_t iterMax = ::atof(argv[4]);
   float threshold = ::atof(argv[5]);
   // Initialize openmp
   KM::initOpenMP(num_threads);
   // sequential benchmark time , parallel benchmark time
   std::vector<std::pair<double, double>> btime(11);
   std::pair<double, double> t;
   for(std::size_t i = 1; i <= 11; i++){
      std::string filename = "data/" + std::to_string(i) + ".csv";
      std::cout << "filename: " << filename << std::endl;
      auto data = CSV::readCSV<float>(filename);
      t = {.0, .0};
      double tbegin, tend;
      for(std::size_t j = 0; j < N; j++){
         tbegin = omp_get_wtime();
         KM::SeqKMeans(data, K, iterMax, threshold);
         tend = omp_get_wtime();
         t.first += tend - tbegin;
      }
      for(std::size_t j = 0; j < N; j++){
          tbegin = omp_get_wtime();
          KM::ParKMeans(data, K, iterMax, threshold);
          tend = omp_get_wtime();
          t.second += tend - tbegin;
       }
       btime[i - 1] = {t.first / double(N), t.second / double(N)};
   }
   // Saving benchmark results
   CSV::writeCSV("data/benchmark.csv", btime);
   return 0;
}
