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
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
Tram::Tram(const unsigned int lijnNr, const unsigned int zitplaatsen, const std::string& beginStation,
	const unsigned int snelheid) :
	lijnNr(lijnNr),
	zitplaatsen(zitplaatsen),
	beginStation(beginStation),
  currentStation(beginStation),
	snelheid(snelheid)
{
	initCheck = this;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
Tram::~Tram() {
}

bool Tram::properlyInitialized() const{
	return initCheck == this;
}

unsigned int Tram::getLijnNr() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getLijnNr");
	return lijnNr;
}

unsigned int Tram::getZitplaatsen() const {
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

unsigned int Tram::getPassagiers() const {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getPassagiers");
    return passagiers;
}

unsigned int Tram::getSnelheid() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getSnelheid");
	return snelheid;
}

void Tram::setLijnNr(const unsigned int newLijnNr) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setLijnNr");
	lijnNr = newLijnNr;
	ENSURE(getLijnNr() == newLijnNr, "setLijnNr post condition failure");
}

void Tram::setZitplaatsen(const unsigned int newZitplaatsen) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setZitplaatsen");
	zitplaatsen = newZitplaatsen;
	ENSURE(getZitplaatsen() == newZitplaatsen,
    "setZitplaatsen post condition failure");
}

void Tram::setBeginStation(const std::string & newBeginStation) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setBeginStation");
	beginStation = newBeginStation;
	ENSURE(getBeginStation() == newBeginStation,
    "setBeginStation post condition failure");
}

void Tram::setCurrentStation(const std::string &newCurrentStation) {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setCurrentStation");
  currentStation = newCurrentStation;
  ENSURE(getCurrentStation() == newCurrentStation,
    "setCurrentStation post condition failure");

}

void Tram::setSnelheid(const unsigned int newSnelheid) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setSnelheid");
	snelheid = newSnelheid;
	ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
}

void Tram::setPassagiers(const unsigned int newPassagiers) {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setPassagiers");
  passagiers = newPassagiers;
  ENSURE(getPassagiers() == newPassagiers,
    "setPassagiers post condition failure");
}

// void Tram::getOff(unsigned int off) {
//   REQUIRE(properlyInitialized(),
//     "Tram wasn't initialized when calling getOff");
//   REQUIRE(off <= getPassagiers(),
//     "More passengers getting off Tram than on Tram");
//   passagiers -= off;
//   ENSURE(getPassagiers() <= getZitplaatsen(),
//     "getOff post condition failure");
// }
//
// void Tram::getOn(unsigned int on) {
//   REQUIRE(properlyInitialized(),
//     "Tram wasn't initialized when calling getOn");
//   REQUIRE(on <= getZitplaatsen() - getPassagiers(),
//     "Not enough seats for passengers getting on Tram");
//   passagiers += on;
//   ENSURE(getPassagiers() <= getZitplaatsen(),
//     "getOn post condition failure");
//
// }
