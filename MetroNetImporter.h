//
//  MetroNetImporter.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 09/03/2017.
//
//

#ifndef MetroNetImporter_h
#define MetroNetImporter_h

#include <iostream>
#include "MetroNet.h"


enum SuccessEnum {ImportAborted, PartialImport, Success};


class MetroNetImporter {
public:

/**
\n REQUIRE(metronet.properlyInitialized(), "metronet wasn't initialized when passed to MetroNetImporter::importMetroNet");
\n ENSURE(result->isConsistent(), "MetroNet is not consistent");
*/
static SuccessEnum importMetroNet(const char * inputfilename, std::ostream& errStream, MetroNet& metronet);

};


#endif /* MetroNetImporter_h */
