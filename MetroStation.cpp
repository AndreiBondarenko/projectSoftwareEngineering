#include "DesignByContract.h"
#include "MetroStation.h"

MetroStation::MetroStation(): Station() {
  	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");	
}

MetroStation::MetroStation(const std::string& naam): Station(naam) {
	REQUIRE(naam != "", "naam must not be empty");
  	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool MetroStation::albatrosCanStop() const {
	REQUIRE(properlyInitialized(), "MetroStation wasn't initialized when calling albatrosCanStop");
	return true;
}