#include "MetroNet.h"
#include "MetroNetImporter.h"
#include <iostream>
#include <fstream>

int main() {
  std::ofstream myfile, error;
  MetroNet antwerpen;
  error.open("_output/MetroNetErrorLog.txt");
  MetroNetImporter::importMetroNet("_input/testInput.xml", error, antwerpen);
	MetroNetImporter::importPassengers("_input/passagiers.xml", error, antwerpen);
  myfile.open("_output/MetroNetLog.txt");
	antwerpen.runSimulation(myfile);
  error.close();
  myfile.close();
  antwerpen.writeToASCII();
  return 0;
}
