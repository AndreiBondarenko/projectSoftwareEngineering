#include "MetroNet.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  MetroNet* antwerpen = MetroNet::initializeFromFile("_input/testInput.xml");
  std::cout << antwerpen->isConsistent() << std::endl;
  std::cout << (antwerpen->getAlleStations())->size() << std::endl;
  return (antwerpen->getAlleStations())->size();
}
