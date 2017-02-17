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
	InitCheck = this;
}
Tram::Tram(const unsigned int lijnNr, const unsigned int zitplaatsen, const std::string& beginStation, 
	const unsigned int snelheid) :
	lijnNr(lijnNr),
	zitplaatsen(zitplaatsen),
	beginStation(beginStation),
	snelheid(snelheid) 
{
	InitCheck = this;
	AantalTrams++;
}
Tram::~Tram() {
	AantalTrams--;
}

bool Tram::properlyInitialized() {
	return InitCheck == this;
}

unsigned int Tram::getLijnNr() const {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLijnNr")
	return LijnNr;
}

unsigned int Tram::getZitplaatsen() const {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getZitplaatsen");
	return Zitplaatsen;
}

std::string Tram::getBeginStation() const {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getBeginStation");
	return BeginStation;
}

unsigned int Tram::getSnelheid() const {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
	return Snelheid;
}

void Tram::setLijnNr(const unsigned int newLijnNr) {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLijnNr");
	LijnNr = newLijnNr;
	ENSURE(this->getLijnNr() == newLijnNr, "setLijnNr post condition failure");
}

void Tram::setZitplaatsen(const unsigned int newZitplaatsen) {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setZitplaatsen");
	Zitplaatsen = newZitplaatsen;
	ENSURE(this->getZitplaatsen() == newZitplaatsen, "setZitplaatsen post condition failure");
}

void Tram::setBeginStation(const std::string & newBeginStation) {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setBeginStation");
	BeginStation = newBeginStation;
	ENSURE(this->getBeginStation() == newBeginStation, "setBeginStation post condition failure");
}

void Tram::setSnelheid(const unsigned int newSnelheid) {
	REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
	Snelheid = newSnelheid;
	ENSURE(this->getSnelheid() == newSnelheid, "setSnelheid post condition failure");
}




