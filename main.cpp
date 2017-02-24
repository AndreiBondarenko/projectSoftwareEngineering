#include "MetroNet.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  MetroNet* antwerpen = MetroNet::initializeFromFile("_input/testInput.xml");
  antwerpen->moveTrams();
  antwerpen->moveTrams();
  antwerpen->moveTrams();
  antwerpen->writeToFile();
  return 0;
}
