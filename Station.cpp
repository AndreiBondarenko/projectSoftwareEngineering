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
  const std::string& volgende, const unsigned int spoor) :
  naam(naam),
  vorige(vorige),
  volgende(volgende),
  spoor(spoor)
{
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

unsigned int Station::getSpoor() const {
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
  naam = newNaam;
  ENSURE(getNaam() == newNaam,
    "setNaam post condition failure");
}

void Station::setVorige(const std::string& newVorige) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setVorige");
  vorige = newVorige;
  ENSURE(getVorige() == newVorige,
    "setVorige post condition failure");
}

void Station::setVolgende(const std::string& newVolgende) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setVolgende");
  volgende = newVolgende;
  ENSURE(getVolgende() == newVolgende,
    "setVolgende post condition failure");
}

void Station::setSpoor(const unsigned int newSpoor) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setSpoor");
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

unsigned int Station::getOpstappen() const {
 REQUIRE(properlyInitialized(),
   "Station wasn't initialized when calling getOpstappen");
 return opstappen;
}

unsigned int Station::getAfstappen() const {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling getAfstappen");
  return afstappen;
}

void Station::setOpstappen(const unsigned int newOpstappen) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setOpstappen");
  opstappen = newOpstappen;
  ENSURE(getOpstappen() == newOpstappen,
    "setOpstappen post condition failure");
}
void Station::setAfstappen(const unsigned int newAfstappen) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setAfstappen");
  afstappen = newAfstappen;
  ENSURE(getAfstappen() == newAfstappen,
    "setAfstappen post condition failure");
}
