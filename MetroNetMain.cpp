#include "MetroNet.h"
#include "MetroNetImporter.h"
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[]) {
  std::ofstream myfile, error;
  MetroNet antwerpen;
  error.open("_output/MetroNetErrorLog.txt");
  MetroNetImporter::importMetroNet("_input/testInput2.xml", myfile, antwerpen);
  myfile.open("_output/MetroNetLog.txt");
  for (int i = 1; i <= 10; i++) {
    myfile << i << ".\n";
  	antwerpen.moveAllePassengers(myfile, error);
  	antwerpen.moveAlleTrams(myfile);
    myfile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  }
  error.close();
  myfile.close();
  antwerpen.writeToASCII();
  return 0;
}
