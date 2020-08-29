#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

#include "Point.hpp"
#include "Cluster.hpp"
#include "SequentialKMeans.hpp"
#include "CSV.hpp"

int main(int argc, char* argv[]){
   if (argc != 4){
      std::cout << "+----------------------------------------------+" << std::endl;
      std::cout << "| Argument Error                               |" << std::endl;
      std::cout << "|                                              |" << std::endl;
      std::cout << "| Usage : ./example filepath outfile nclusters |" << std::endl;
      std::cout << "+----------------------------------------------+" << std::endl;
      return 1;
   }
   
   auto filepath = std::string(argv[1]);
   auto outfile = std::string(argv[2]);
   std::size_t nclusters = ::atof(argv[3]);
   
   // Importing dataset
   auto data = CSV::readCSV<float>(filepath);

   // Runing KMeans clustering algorithm
   auto cluster = KM::SeqKMeans(data, nclusters);

   // Exporting clusters
   CSV::writeCSV(outfile, data);

   return 0;
}