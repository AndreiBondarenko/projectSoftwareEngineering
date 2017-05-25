#include "DesignByContract.h"
#include "Halte.h"

Halte::Halte(): Station() {
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Halte::Halte(const std::string& naam): Station(naam) {
	REQUIRE(naam != "", "naam must not be empty");
  	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Halte::albatrosCanStop() const {
	REQUIRE(properlyInitialized(), "Halte wasn't initialized when calling albatrosCanStop");
	return false;
}