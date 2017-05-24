#include "DesignByContract.h"
#include "Halte.h"

Halte::Halte(): Station() {}

Halte::Halte(const std::string& naam): Station(naam) {}

bool Halte::albatrosCanStop() const {
	REQUIRE(properlyInitialized(), "Halte wasn't initialized when calling albatrosCanStop");
	return false;
}