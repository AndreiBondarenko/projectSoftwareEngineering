#include "DesignByContract.h"
#include "MetroStation.h"

MetroStation::MetroStation(): Station() {}

MetroStation::MetroStation(const std::string& naam): Station(naam) {}

bool MetroStation::albatrosCanStop() const {
	REQUIRE(properlyInitialized(), "MetroStation wasn't initialized when calling albatrosCanStop");
	return true;
}