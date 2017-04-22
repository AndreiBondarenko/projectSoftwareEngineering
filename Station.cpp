//
//  Station.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#include "Station.h"
#include "DesignByContract.h"

Station::Station()  {
  initCheck = this;
  opstappen = 0;
  afstappen = 0;
  tramInStation = {};
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}

// Station::Station(const std::string& naam, const std::string& vorige,
//   const std::string& volgende, const int spoor) :
//   naam(naam),
//   vorige(vorige),
//   volgende(volgende),
//   spoor(spoor)
// {
//   REQUIRE(volgende != "", "volgende must not be empty");
//   REQUIRE(vorige != "", "vorige must not be empty");
//   REQUIRE(naam != "", "naam must not be empty");
//   REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
//   initCheck = this;
//   opstappen = 0;
//   afstappen = 0;
//   tramInStation = false;
//   ENSURE(properlyInitialized(),
//     "constructor must end in properlyInitialized state");
// }

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

std::string Station::getVorige(const int& spoor) const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getVorige");
  REQUIRE(spoor >= 0,
    "parameter spoor must be >= 0, when passed to getVorige");
  return vorige.at(spoor);

}

std::string Station::getVolgende(const int& spoor) const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getVolgende");
  REQUIRE(spoor >= 0,
    "parameter spoor must be >= 0, when passed to getVolgende");
  return volgende.at(spoor);
}

std::string Station::getType() const {
  REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getType");
  return type;
}

std::set<int> Station::getSporen() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getSpoor");
  std::set<int> sporen;
  for(auto mapIt = vorige.begin(); mapIt != vorige.end(); mapIt++) {
    sporen.insert(mapIt->first);
  }
  return sporen;
}

bool Station::isTramInStation(const int& spoor) const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getTramInStation");
  REQUIRE(spoor >= 0,
    "parameter spoor must be >= 0, when passed to isTramInStation");
  return tramInStation.at(spoor);
}

void Station::setNaam(const std::string& newNaam) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setNaam");
  REQUIRE(newNaam != "", "newNaam must not be empty");
  naam = newNaam;
  ENSURE(getNaam() == newNaam,
    "setNaam post condition failure");
}

void Station::addVorige(const int& spoor, const std::string& newVorige) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setVorige");
  REQUIRE(newVorige != "", "newVorige must not be empty");
  vorige[spoor] = newVorige;
  ENSURE(getVorige(spoor) == newVorige,
    "setVorige post condition failure");
}

void Station::addVolgende(const int& spoor, const std::string& newVolgende) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setVolgende");
  REQUIRE(newVolgende != "", "newVolgende must not be empty");
  volgende[spoor] = newVolgende;
  ENSURE(getVolgende(spoor) == newVolgende,
    "setVolgende post condition failure");
}

void Station::setType(const std::string& newType) {
    REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setType");
    REQUIRE(newType != "", "newType must not be empty");
    type = newType;
    ENSURE(getType() == newType, "setType post condition failure");
}

void Station::setTramInStation(const int& spoor, const bool& newTramInStation) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setTramInStation");
  tramInStation[spoor] = newTramInStation;
  ENSURE(isTramInStation(spoor) == newTramInStation,
    "setTramInStation post condition failure");
}

// OPTIONAL

int Station::getOpstappen() const {
 REQUIRE(properlyInitialized(),
   "Station wasn't initialized when calling getOpstappen");
 return opstappen;
}

int Station::getAfstappen() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getAfstappen");
  return afstappen;
}

void Station::setOpstappen(const int newOpstappen) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setOpstappen");
  REQUIRE(newOpstappen >= 0 , "newOpstappen must be bigger or equal to zero");
  opstappen = newOpstappen;
  ENSURE(getOpstappen() == newOpstappen,
    "setOpstappen post condition failure");
}
void Station::setAfstappen(const int newAfstappen) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setAfstappen");
  REQUIRE(newAfstappen >= 0 , "newAfstappen must be bigger or equal to zero");
  afstappen = newAfstappen;
  ENSURE(getAfstappen() == newAfstappen,
    "setAfstappen post condition failure");
}
