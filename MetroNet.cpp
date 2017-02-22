//
//  MetroNet.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#include "MetroNet.h"
#include "DesignByContract.h"
#include <iostream>

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

bool MetroNet::isConsistent() const {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling isConsistent");
  // elk station is verbonden met een voorgaand en een volgend station
  // voor elk spoor
  for(auto mapIt = alleStations.begin(); mapIt != alleStations.end(); ++mapIt) {
    std::string vorige = mapIt->second->getVorige();
    std::string volgende = mapIt->second->getVolgende();
    if (alleStations.find(vorige) == alleStations.end() ||
        alleStations.find(volgende) == alleStations.end()) {
      return false;
    }
  }
  // er bestaan geen trams met een lijn nummer dat niet overeenkomt met een
  // spoor in een station
  // het beginstation van een tram een geldig station in het metronet is
  for(auto mapIt = alleTrams.begin(); mapIt != alleTrams.end(); ++mapIt) {
    unsigned int lijnNr = mapIt->second->getLijnNr();
    std::string beginStation = mapIt->second->getBeginStation();
    if (alleSporen.find(lijnNr) == alleSporen.end()) {
      return false;
    }
    if (alleStations.find(beginStation) == alleStations.end()) {
      return false;
    }
  }
  // er geen sporen zijn waarvoor geen tram bestaat
  for(auto setIt = alleSporen.begin(); setIt != alleSporen.end(); ++setIt) {
    unsigned int spoor = *setIt;
    if (alleTrams.find(spoor) == alleTrams.end()) {
      return false;
    }
  }
  // elk spoor maximaal een keer door elk station komt ???????????????????????
  return true;
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
  alleSporen.insert(newStation->getSpoor());
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
