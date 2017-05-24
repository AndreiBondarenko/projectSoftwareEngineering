#include "PCC.h"
#include <iostream>
#include "DesignByContract.h"

#include "MetroNet.h"

PCC::PCC() : Tram() {}

PCC::PCC(const int lijnNr, const int voertuigNr,
         const int zitplaatsen, const std::string& beginStation,
         const int snelheid)
    : Tram(lijnNr, voertuigNr, zitplaatsen, beginStation, snelheid) {}

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
