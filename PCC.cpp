#include "PCC.h"
#include <iostream>
#include "DesignByContract.h"

#include "MetroNet.h"

PCC::PCC() : Tram() {
	zitplaatsen = 16;
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

PCC::PCC(const int lijnNr, const int voertuigNr,
         const int zitplaatsen, const std::string& beginStation,
         const int snelheid)
    : Tram(lijnNr, voertuigNr, zitplaatsen, beginStation, snelheid) {
	REQUIRE(beginStation != "", "newBeginStation must not be empty");
  	REQUIRE(lijnNr >= 0 , "lijnNr must be bigger or equal to zero");
  	REQUIRE(voertuigNr >= 0 , "voertuigNr must be bigger or equal to zero");
  	REQUIRE(zitplaatsen >= 0 , "zitplaatsen must be bigger or equal to zero");
  	REQUIRE(snelheid >= 0 , "snelheid must be bigger or equal to zero");
  	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");	
	}

PCC::~PCC() {}

bool PCC::stoptInStation(MetroNet& metronet, std::string station) const {
	REQUIRE(properlyInitialized(), "PCC wasn't initialized when calling afstappenInHalte");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling afstappenInHalte");
	REQUIRE(station != "", "station must not be empty");
    std::string current = getCurrentStation();
    if (current == station) {
        return true;
	}
    std::string nextStation = metronet.getStation(current)->getVolgende(lijnNr);
	while (nextStation != current) {
		if (nextStation == station) {
			return true;
		}
		nextStation = metronet.getStation(nextStation)->getVolgende(lijnNr);
	}
	return false;
}
