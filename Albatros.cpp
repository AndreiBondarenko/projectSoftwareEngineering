#include "Albatros.h"
#include <iostream>
#include "DesignByContract.h"

#include "MetroNet.h"

Albatros::Albatros() : Tram() {
	zitplaatsen = 72;
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Albatros::Albatros(const int lijnNr, const int voertuigNr,
         const int zitplaatsen, const std::string& beginStation,
         const int snelheid)
    : Tram(lijnNr, voertuigNr,zitplaatsen, beginStation, snelheid) {
	REQUIRE(beginStation != "", "newBeginStation must not be empty");
  	REQUIRE(lijnNr >= 0 , "lijnNr must be bigger or equal to zero");
  	REQUIRE(voertuigNr >= 0 , "voertuigNr must be bigger or equal to zero");
  	REQUIRE(zitplaatsen >= 0 , "zitplaatsen must be bigger or equal to zero");
  	REQUIRE(snelheid >= 0 , "snelheid must be bigger or equal to zero");
  	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
	}

Albatros::~Albatros() {}

bool Albatros::stoptInStation(MetroNet& metronet, std::string station) const {
	REQUIRE(properlyInitialized(), "Albatros wasn't initialized when calling stoptInStation");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling stoptInStation");
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
