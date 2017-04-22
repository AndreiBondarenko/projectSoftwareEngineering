#include "Station.h"
#include "DesignByContract.h"
#include <iostream>
#include <algorithm>

Station::Station()  {
  initCheck = this;
  opstappen = 0;
  afstappen = 0;
  tramInStation = false;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}

Station::Station(const std::string& naam, const std::string& vorige,
  const std::string& volgende, const int spoor) :
  naam(naam),
  vorige(vorige),
  volgende(volgende),
  spoor(spoor)
{
  REQUIRE(volgende != "", "volgende must not be empty");
  REQUIRE(vorige != "", "vorige must not be empty");
  REQUIRE(naam != "", "naam must not be empty");
  REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  initCheck = this;
  opstappen = 0;
  afstappen = 0;
  tramInStation = false;
	ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}

Station::~Station() {
}

bool Station::properlyInitialized() const {
  return initCheck == this;
}

std::string Station::getNaam() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getNaam");
  return naam;
}

std::string Station::getVorige() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getVorige");
  return vorige;
}

std::string Station::getVolgende() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getVolgende");
  return volgende;
}

std::string Station::getType() const {
  REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getType");
  return type;
}

int Station::getSpoor() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getSpoor");
  return spoor;
}

bool Station::isTramInStation() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getTramInStation");
  return tramInStation;
}

void Station::setNaam(const std::string& newNaam) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setNaam");
  REQUIRE(newNaam != "", "newNaam must not be empty");
  naam = newNaam;
  ENSURE(getNaam() == newNaam,
    "setNaam post condition failure");
}

void Station::setVorige(const std::string& newVorige) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setVorige");
  REQUIRE(newVorige != "", "newVorige must not be empty");
  vorige = newVorige;
  ENSURE(getVorige() == newVorige,
    "setVorige post condition failure");
}

void Station::setVolgende(const std::string& newVolgende) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setVolgende");
  REQUIRE(newVolgende != "", "newVolgende must not be empty");
  volgende = newVolgende;
  ENSURE(getVolgende() == newVolgende,
    "setVolgende post condition failure");
}

void Station::setType(const std::string& newType) {
    REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setType");
    REQUIRE(newType != "", "newType must not be empty");
    type = newType;
    ENSURE(getType() == newType, "setType post condition failure");

}

void Station::setSpoor(const int newSpoor) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setSpoor");
  REQUIRE(newSpoor >= 0 , "newSpoor must be bigger or equal to zero");
  spoor = newSpoor;
  ENSURE(getSpoor() == newSpoor,
    "setSpoor post condition failure");
}

void Station::setTramInStation(bool newTramInStation) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setTramInStation");
  tramInStation = newTramInStation;
  ENSURE(isTramInStation() == newTramInStation,
    "setTramInStation post condition failure");
}

bool Station::isInStation(std::string passagier) {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling isInStation");
	REQUIRE(passagier != "", "passagier must not be empty");
	return passagiers.find(passagier) != passagiers.end();
}

void Station::addPassagier(std::string passagier) {

	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling addPassagier");
	REQUIRE(passagier != "", "passagier must not be empty");
	REQUIRE(isInStation(passagier) == false, "passenger allready in Station");
	passagiers.insert(passagier);
	ENSURE(isInStation(passagier) == true, "addPassagier post condition failure");
}

void Station::removePassagier(std::string passagier) {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling removePassagier");
	REQUIRE(passagier != "", "passagier must not be empty");
	REQUIRE(isInStation(passagier) == true, "passenger not in Station");
	passagiers.erase(passagier);
	ENSURE(isInStation(passagier) == false, "removePassagier post condition failure");
}

void Station::movePassagiers(MetroNet& metronet, std::ostream& output, std::ostream& error) {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling movePassagiers");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling movePassagiers");
	Tram* tram; // = getTramInStation(metronet);
	if (tram == nullptr) {
		return;
	}
	for (std::string passagierName : passagiers) {
		Passagier* passagier = metronet.getPassagier(passagierName);
		if (passagier->getBeginStation() == naam) {
			tram->addPassagier(passagierName);
			removePassagier(passagierName);
		}
	}
}
