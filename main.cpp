#include "BestandIO.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  MetroNet* antwerpen = BestandIO::initialize("_input/testInput.xml");
  std::cout << (antwerpen->getAlleStations())->size() << std::endl;
  return (antwerpen->getAlleStations())->size();
}
