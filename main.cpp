#include "MetroNet.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    MetroNet* antwerpen = MetroNet::initializeFromFile("_input/testInput.xml");
    antwerpen->moveTrams();
    antwerpen->moveTrams();
    antwerpen->moveTrams();
    antwerpen->writeToFile();
  }
  else if (argc == 2) {
    MetroNet* antwerpen = MetroNet::initializeFromFile(argv[1]);
    antwerpen->moveTrams();
    antwerpen->moveTrams();
    antwerpen->moveTrams();
    antwerpen->writeToFile();
  }
  else {
    MetroNet* antwerpen = MetroNet::initializeFromFile(argv[1]);
    antwerpen->simulate(argv[2]);
  }
  return 0;
}
