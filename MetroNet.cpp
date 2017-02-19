//
//  MetroNet.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#include "MetroNet.h"
#include "DesignByContract.h"

MetroNet::MetroNet()  {
  initCheck = this;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
MetroNet::~MetroNet() {
  for(auto it = alleStations.begin(); it != alleStations.end(); ++it) {
      delete it->second;
  }
  for(auto it = alleTrams.begin(); it != alleTrams.end(); ++it) {
      delete it->second;
  }
  alleStations.clear();
  alleTrams.clear();
  alleSporen.clear();
}

bool MetroNet::properlyInitialized() const {
  return initCheck == this;
}

std::map<std::string, Station*>* MetroNet::getAlleStations() {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling getAlleStations");
  return &alleStations;
}

std::map<int, Tram*>* MetroNet::getAlleTrams() {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling getAlleTrams");
  return &alleTrams;
}

std::set<unsigned int>* MetroNet::getAlleSporen() {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling getAlleSporen");
  return &alleSporen;
}

void MetroNet::setAlleStations(std::map<std::string, Station*>& newAlleStations) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling setAlleStations");
  alleStations = newAlleStations;
  ENSURE(*getAlleStations() == newAlleStations,
    "setAlleStations post condition failure");
}

void MetroNet::setAlleTrams(std::map<int, Tram*>& newAlleTrams) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling setAlleTrams");
  alleTrams = newAlleTrams;
  ENSURE(*getAlleTrams() == newAlleTrams,
    "setAlleTrams post condition failure");
}

void MetroNet::setAlleSporen(std::set<unsigned int>& newAlleSporen) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling setAlleSporen");
  alleSporen = newAlleSporen;
  ENSURE(*getAlleSporen() == newAlleSporen,
    "setAlleSporen post condition failure");
}

void MetroNet::addStation(Station* newStation) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling addStation");
  REQUIRE(getAlleStations()->count(newStation->getNaam()) == 0,
    "This MetroNet already contains a station with this name");
  alleStations[newStation->getNaam()] = newStation;
  ENSURE(getAlleStations()->at(newStation->getNaam()) == newStation,
    "addStation post condition failure");
}

void MetroNet::removeStation(const std::string& stationName) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling removeStation");
  REQUIRE(getAlleStations()->count(stationName) == 1,
    "This MetroNet doesn't contain a station with this name");
  alleStations.erase(stationName);
  ENSURE(getAlleStations()->count(stationName) == 0,
    "removeStation post condition failure");
}

void MetroNet::addTram(Tram* newTram) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling addTram");
  REQUIRE(getAlleTrams()->count(newTram->getLijnNr()) == 0,
    "This MetroNet already contains a Tram with this lijnNr");
  alleTrams[newTram->getLijnNr()] = newTram;
  ENSURE(getAlleTrams()->at(newTram->getLijnNr()) == newTram,
    "addTram post condition failure");
}

void MetroNet::removeTram(const unsigned int lijnNr) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling removeTram");
  REQUIRE(getAlleTrams()->count(lijnNr) == 1,
    "This MetroNet doesn't contain a tram with this lijnNr");
  alleTrams.erase(lijnNr);
  ENSURE(getAlleTrams()->count(lijnNr) == 0,
    "removeTram post condition failure");
}
