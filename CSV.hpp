#pragma once

#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "Cluster.hpp"
#include "Point.hpp"

namespace CSV {

using KM::Cluster;
using KM::Point;

template <typename T> Point<T> getNextLine(std::istream &str, char sep) {
  std::vector<T> rowData;
  std::string line;
  std::getline(str, line);
  std::stringstream lineStr(line);
  std::string cell;
  while (std::getline(lineStr, cell, sep))
    rowData.push_back(::atof(cell.c_str()));
  return Point<T>(rowData);
}

// Read data from csv file
template <typename T>
std::vector<Point<T>> readCSV(const std::string &filename, char sep = ',') {
  std::ifstream file(filename);
  std::vector<Point<T>> data;
  while (!file.eof())
    data.push_back(getNextLine<T>(file, sep));
  file.close();
  // FIXME Read unecessary line
  data.pop_back();
  return data;
}

template <typename T>
void writeNextLine(std::ostream &str, const Point<T> &point) {
  auto &coord = point.GetCoord();
  std::string line;
  for (auto &x : point.GetCoord())
    str << x << ' ';
  str << point.GetClusterId() << '\n';
}

// save data to csv file
template <typename T>
void writeCSV(const std::string &filename, const std::vector<Point<T>> &data) {
  std::ofstream file(filename);
  for (auto &P : data)
    writeNextLine(file, P);
  file.close();
}

} // namespace CSV
