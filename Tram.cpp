//
//  Tram.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#include "Tram.h"
#include "DesignByContract.h"

Tram::Tram()  {
	initCheck = this;
  	// aantalTrams++;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}
Tram::Tram(const unsigned int lijnNr, const unsigned int zitplaatsen, const std::string& beginStation,
	const unsigned int snelheid) :
	lijnNr(lijnNr),
	zitplaatsen(zitplaatsen),
	beginStation(beginStation),
	snelheid(snelheid)
{
	initCheck = this;
	// aantalTrams++;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}
Tram::~Tram() {
	// aantalTrams--;
}

bool Tram::properlyInitialized() const{
	return initCheck == this;
}

unsigned int Tram::getLijnNr() const {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getLijnNr");
	return lijnNr;
}

unsigned int Tram::getZitplaatsen() const {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getZitplaatsen");
	return zitplaatsen;
}

std::string Tram::getBeginStation() const {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getBeginStation");
	return beginStation;
}

unsigned int Tram::getSnelheid() const {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
	return snelheid;
}

void Tram::setLijnNr(const unsigned int newLijnNr) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setLijnNr");
	lijnNr = newLijnNr;
	ENSURE(getLijnNr() == newLijnNr, "setLijnNr post condition failure");
}

void Tram::setZitplaatsen(const unsigned int newZitplaatsen) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setZitplaatsen");
	zitplaatsen = newZitplaatsen;
	ENSURE(getZitplaatsen() == newZitplaatsen, "setZitplaatsen post condition failure");
}

void Tram::setBeginStation(const std::string & newBeginStation) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setBeginStation");
	beginStation = newBeginStation;
	ENSURE(getBeginStation() == newBeginStation, "setBeginStation post condition failure");
}

void Tram::setSnelheid(const unsigned int newSnelheid) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
	snelheid = newSnelheid;
	ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
}
