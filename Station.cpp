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
