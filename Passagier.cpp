#include "Passagier.h"
#include "DesignByContract.h"
#include <iostream>

Passagier::Passagier() {
	initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Passagier::Passagier(std::string naam, std::string beginStation, std::string eindStation, int hoeveelheid) :
 	naam(naam),
 	beginStation(beginStation),
 	eindStation(eindStation),
 	hoeveelheid(hoeveelheid)
{
	REQUIRE(naam != "", "naam must not be empty");
	REQUIRE(beginStation != "", "beginStation must not be empty");
	REQUIRE(eindStation != "", "eindStation must not be empty");
	REQUIRE(hoeveelheid >= 0 , "hoeveelheid must be bigger or equal to zero");
	initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Passagier::~Passagier() {
}

bool Passagier::properlyInitialized() const{
	return initCheck == this;
}

std::string Passagier::getNaam() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getNaam");
	return naam;
}

std::string Passagier::getBeginStation() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getBeginStation");
	return beginStation;
}

std::string Passagier::getEindStation() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getEindStation");
	return eindStation;
}

int Passagier::getHoeveelheid() const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getHoeveelheid");
	return hoeveelheid;
}

void Passagier::setNaam(const std::string& newNaam) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setNaam");
	REQUIRE(newNaam != "" , "newNaam must not be empty");
	naam = newNaam;
	ENSURE(getNaam() == newNaam, "setNaam post condition failure");
}

void Passagier::setBeginStation(const std::string& newBeginStation) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setBeginStation");
	REQUIRE(newBeginStation != "" , "newBeginStation must not be empty");
	beginStation = newBeginStation;
	ENSURE(getBeginStation() == newBeginStation, "setBeginStation post condition failure");
}

void Passagier::setEindStation(const std::string& newEindStation) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setEindStation");
	REQUIRE(newEindStation != "" , "newEindStation must not be empty");
	eindStation = newEindStation;
	ENSURE(getEindStation() == newEindStation, "setEindStation post condition failure");
}

void Passagier::setHoeveelheid(const int newHoeveelheid) {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setHoeveelheid");
	REQUIRE(newHoeveelheid >= 0 , "newHoeveelheid must be bigger or equal to zero");
	hoeveelheid = newHoeveelheid;
	ENSURE(getHoeveelheid() == newHoeveelheid, "setHoeveelheid post condition failure");
}

void Passagier::moveToBeginStation(MetroNet& metronet) const {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling moveToBeginStation");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling Passagier::moveToBeginStation");
	REQUIRE(metronet.getStation(beginStation) != nullptr, "beginStation is not a station of MetroNet");
	Station* station = metronet.getStation(beginStation);
	station->addPassagier(naam);
	ENSURE(station->isInStation(naam), "moveToBeginStation post condition failure");
	ENSURE(metronet.isConsistent(), "Passagier::moveToBeginStation made MetroNet inconsistent");
}

bool Passagier::isAangekomen() const {
    REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling isAangekomen");
    return aangekomen;
}

void Passagier::markAangekomen() {
	REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling markAangekomen");
	aangekomen = true;
	ENSURE(isAangekomen() == true, "markAangekomen post condition failure");
}
