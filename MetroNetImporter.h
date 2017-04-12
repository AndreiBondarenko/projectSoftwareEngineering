#ifndef MetroNetImporter_h
#define MetroNetImporter_h

#include <iostream>
#include "MetroNet.h"


enum SuccessEnum {ImportAborted, PartialImport, Success};


class MetroNetImporter {
public:

/**
\n REQUIRE(metronet.properlyInitialized(), "metronet wasn't initialized when passed to MetroNetImporter::importMetroNet");
\n ENSURE(metronet.isConsistent(), "MetroNet is not consistent");
*/
static SuccessEnum importMetroNet(const char * inputfilename, std::ostream& errStream, MetroNet& metronet);
/**
\n REQUIRE(metronet.properlyInitialized(), "metronet wasn't initialized when passed to MetroNetImporter::importPassengers");
\n ENSURE(metronet.isConsistent(), "MetroNet is not consistent");
*/
static SuccessEnum importPassengers(const char* inputfilename, std::ostream& errStream, MetroNet& metronet);
};


#endif /* MetroNetImporter_h */
