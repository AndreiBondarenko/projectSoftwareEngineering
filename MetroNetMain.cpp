#include "MetroNet.h"
#include "MetroNetImporter.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	if (argc != 3 && argc != 4) {
		std::cerr << "use: metronet.xml passengers.xml (-l)\n";
		return -1;
	}
  else if (argc == 4 && argv[3] == std::string("-l")){
    MetroNet net;
    MetroNetImporter::importMetroNet(argv[1], std::cerr, net);
	  MetroNetImporter::importPassengers(argv[2], std::cerr, net);
    net.runSimulation(std::cout, true);
  }
  else 
  {
    std::ofstream operationLog, errorLog;
    MetroNet net;
    errorLog.open("_output/MetroNetErrorLog.txt");
    MetroNetImporter::importMetroNet(argv[1], errorLog, net);
	  MetroNetImporter::importPassengers(argv[2], errorLog, net);
    operationLog.open("_output/MetroNetOperationLog.txt");
    net.runSimulation(operationLog);
    errorLog.close();
    operationLog.close();
    net.writeToASCII();    
  }
  return 0;
}
