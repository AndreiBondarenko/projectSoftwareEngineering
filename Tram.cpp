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
  passagiers = 0;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
Tram::Tram(const int lijnNr, const int zitplaatsen, const std::string& beginStation,
	const int snelheid) :
	lijnNr(lijnNr),
	zitplaatsen(zitplaatsen),
	beginStation(beginStation),
  currentStation(beginStation),
	snelheid(snelheid)
{
  REQUIRE(beginStation != "", "beginStation must not be empty");
  REQUIRE(lijnNr >= 0 , "lijnNr must be bigger or equal to zero");
  REQUIRE(zitplaatsen >= 0 , "zitplaatsen must be bigger or equal to zero");
  REQUIRE(snelheid >= 0 , "snelheid must be bigger or equal to zero");
	initCheck = this;
  passagiers = 0;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
Tram::~Tram() {
}

bool Tram::properlyInitialized() const{
	return initCheck == this;
}

int Tram::getLijnNr() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getLijnNr");
	return lijnNr;
}

int Tram::getZitplaatsen() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getZitplaatsen");
	return zitplaatsen;
}

std::string Tram::getBeginStation() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getBeginStation");
	return beginStation;
}

std::string Tram::getCurrentStation() const {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getCurrentStation");
  return currentStation;
}

int Tram::getPassagiers() const {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getPassagiers");
    return passagiers;
}

int Tram::getSnelheid() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getSnelheid");
	return snelheid;
}

void Tram::setLijnNr(const int newLijnNr) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setLijnNr");
  REQUIRE(newLijnNr >= 0 , "newLijnNr must be bigger or equal to zero");

	lijnNr = newLijnNr;
	ENSURE(getLijnNr() == newLijnNr, "setLijnNr post condition failure");
}

void Tram::setZitplaatsen(const int newZitplaatsen) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setZitplaatsen");
  REQUIRE(newZitplaatsen >= 0 ,
    "newZitplaatsen must be bigger or equal to zero");
	zitplaatsen = newZitplaatsen;
	ENSURE(getZitplaatsen() == newZitplaatsen,
    "setZitplaatsen post condition failure");
}

void Tram::setBeginStation(const std::string & newBeginStation) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setBeginStation");
  REQUIRE(newBeginStation != "", "newBeginStation must not be empty");
	beginStation = newBeginStation;
	ENSURE(getBeginStation() == newBeginStation,
    "setBeginStation post condition failure");
}

void Tram::setCurrentStation(const std::string &newCurrentStation) {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setCurrentStation");
  REQUIRE(newCurrentStation != "", "newCurrentStation must not be empty");
  currentStation = newCurrentStation;
  ENSURE(getCurrentStation() == newCurrentStation,
    "setCurrentStation post condition failure");

}

void Tram::setSnelheid(const int newSnelheid) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setSnelheid");
  REQUIRE(newSnelheid >= 0 , "newSnelheid must be bigger or equal to zero");
	snelheid = newSnelheid;
	ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
}

void Tram::setPassagiers(const int newPassagiers) {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setPassagiers");
  REQUIRE(newPassagiers >= 0 , "newPassagiers must be bigger or equal to zero");
  passagiers = newPassagiers;
  ENSURE(getPassagiers() == newPassagiers,
    "setPassagiers post condition failure");
}
