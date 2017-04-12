#include "Passagier.h"

Passagier::PAssagier() {
	initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Passagier(std::string naam, std::string beginStation, std::string eindStation, int hoeveelheid) :
 	naam(naam),
 	beginStation(beginStation),
 	eindStation(eindStation),
 	hoeveelheid(hoeveelheid)
{
	REQUIRE(naam != "", "naam must not be empty");
	REQUIRE(beginStation != "", "newBeginStation must not be empty");
	REQUIRE(eindStation != "", "newEindStation must not be empty");
	REQUIRE(hoeveelheid >= 0 , "hoeveelheid must be bigger or equal to zero");
	initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

~Passagier() {
}

bool Passagier::properlyInitialized() const{
	return initCheck == this;
}

std::string getNaam() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getNaam");
	return naam;
}

std::string getBeginStation() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getBeginStation");
	return beginStation;
}

std::string getEindStation() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getEindStation");
	return eindStation;
}

int getHoeveelheid() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getHoeveelheid");
	return hoeveelheid;
}

void setNaam(const std::string& newNaam) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setNaam");
	REQUIRE(newNaam != "" , "newNaam must not be empty");
	naam = newNaam;
	ENSURE(getNaam() == newNaam, "setNaam post condition failure");
}

void setBeginStation(const std::string& newBeginStation) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setBeginStation");
	REQUIRE(newBeginStation != "" , "newBeginStation must not be empty");
	beginStation = newBeginStation;
	ENSURE(getBeginStation() == newBeginStation, "setBeginStation post condition failure");
}

void setEindStation(const std::string& newEindStation) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setEindStation");
	REQUIRE(newEindStation >= 0 , "newEindStation must not be empty");
	eindStation = newEindStation;
	ENSURE(getEindStation() == newEindStation, "setEindStation post condition failure");
}

void setHoeveelheid(const int newHoeveelheid) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setHoeveelheid");
	REQUIRE(newHoeveelheid >= 0 , "newHoeveelheid must be bigger or equal to zero");
	hoeveelheid = newHoeveelheid;
	ENSURE(getHoeveelheid() == newHoeveelheid, "setHoeveelheid post condition failure");
}