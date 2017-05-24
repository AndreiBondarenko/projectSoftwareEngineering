#include "Albatros.h"
#include <iostream>
#include "DesignByContract.h"

#include "MetroNet.h"

Albatros::Albatros() : Tram() {}

Albatros::Albatros(const int lijnNr, const int voertuigNr,
         const int zitplaatsen, const std::string& beginStation,
         const int snelheid)
    : Tram(lijnNr, voertuigNr,zitplaatsen, beginStation, snelheid) {}

Albatros::~Albatros() {}

bool Albatros::stoptInStation(MetroNet& metronet, std::string station) const {
	REQUIRE(properlyInitialized(), "Albatros wasn't initialized when calling afstappenInHalte");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling afstappenInHalte");
	REQUIRE(station != "", "station must not be empty");
    std::string current = getCurrentStation();
    if (current == station) {
		if (!metronet.getStation(station)->albatrosCanStop()) return false;
        return true;
	}
    std::string nextStation = metronet.getStation(current)->getVolgende(lijnNr);
	while (nextStation != current) {
		if (nextStation == station) {
			if (!metronet.getStation(station)->albatrosCanStop()) return false;
			return true;
		}
		nextStation = metronet.getStation(nextStation)->getVolgende(lijnNr);
	}
	return false;
}
