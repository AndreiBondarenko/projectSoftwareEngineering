#include "MetroNet.h"
#include "MetroNetImporter.h"
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[]) {
  std::ofstream myfile;
  MetroNet antwerpen;
  myfile.open("_output/zzzError.txt");
  MetroNetImporter::importMetroNet("_input/testInput.xml", myfile, antwerpen);
  myfile.close();
  antwerpen.writeToASCII();
  return 0;
}
