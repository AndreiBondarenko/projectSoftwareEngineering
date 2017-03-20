//
//  MetroNet.cpp
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#include "MetroNet.h"
#include "tinyxml.h"
#include "DesignByContract.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

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
    int lijnNr = mapIt->second->getLijnNr();
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
    int spoor = *setIt;
    if (alleTrams.find(spoor) == alleTrams.end()) {
      return false;
    }
  }
  // elk spoor maximaal een keer door elk station komt ???????????????????????
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

std::set<int>* MetroNet::getAlleSporen() {
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

void MetroNet::setAlleSporen(std::set<int>& newAlleSporen) {
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

void MetroNet::addTram(Tram* newTram) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling addTram");
  REQUIRE(getAlleTrams()->count(newTram->getLijnNr()) == 0,
    "This MetroNet already contains a Tram with this lijnNr");
  alleTrams[newTram->getLijnNr()] = newTram;
  alleStations[newTram->getBeginStation()]->setTramInStation(true);
  ENSURE(getAlleTrams()->at(newTram->getLijnNr()) == newTram,
    "addTram post condition failure");
  ENSURE(getAlleStations()->at(newTram->getBeginStation())->isTramInStation(),
    "addTram post condition failure");
}

void MetroNet::moveTram(std::string station, int spoor, std::ostream& output) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling moveTrams");
  REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  REQUIRE(station != "", "station must not be empty");
  std::string currentStation = getAlleTrams()->at(spoor)->getCurrentStation();
  getAlleStations()->at(currentStation)->setTramInStation(false);
  getAlleTrams()->at(spoor)->setCurrentStation(station);
  getAlleStations()->at(station)->setTramInStation(true);
  output << "Tram " << spoor << " reed van station " << currentStation << " naar station " << station << ".\n";
  ENSURE(getAlleStations()->at(station)->isTramInStation(),
    "moveTram post condition failure");
  ENSURE(station == getAlleTrams()->at(spoor)->getCurrentStation(),
    "moveTram post condition failure");
  ENSURE(isConsistent(), "moveTram made MetroNet inconsistent");
}

void MetroNet::moveAlleTrams(std::ostream& output) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAlleTrams");
  for (auto& tram : alleTrams) {
    moveTram(getAlleStations()->at(tram.second->getCurrentStation())->getVolgende(), tram.first, output);
  }

  ENSURE(isConsistent(), "moveAlleTrams made MetroNet inconsistent");
}

void MetroNet::movePassengers(std::string station, int spoor, std::ostream& output, std::ostream& error) {
  REQUIRE(properlyInitialized(),
    "MetroNet wasn't initialized when calling movePassengers");
  REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  REQUIRE(station != "", "station must not be empty");
  REQUIRE(getAlleTrams()->at(spoor)->getCurrentStation() == station,
    "Tram not in given station");
  REQUIRE(getAlleStations()->at(station)->isTramInStation(),
    "Station is empty");
  const int afstappen = getAlleStations()->at(station)->getAfstappen();
  const int opstappen = getAlleStations()->at(station)->getOpstappen();
  int passagiers = getAlleTrams()->at(spoor)->getPassagiers();
  const int zitplaatsen = getAlleTrams()->at(spoor)->getZitplaatsen();
  if(afstappen <= passagiers){
    getAlleTrams()->at(spoor)->setPassagiers(passagiers-afstappen);
    output << "In station " << station << " stappen " << afstappen << " mensen af tram "
    << spoor << ".\n";
  }
  else {
    output << "In station " << station << " stappen " << passagiers << " mensen af tram "
    << spoor << ".\n";
    getAlleTrams()->at(spoor)->setPassagiers(0);
    error << "ERROR: Aan station " << station << " stappen " << afstappen
    << " mensen af tram " << spoor << ". Slechts " << passagiers << " mensen op de tram.\n";
  }
  passagiers = getAlleTrams()->at(spoor)->getPassagiers();
  if(passagiers + opstappen <= zitplaatsen){
    getAlleTrams()->at(spoor)->setPassagiers(passagiers+opstappen);
    output << "In station " << station << " stappen " << opstappen << " mensen op tram "
    << spoor << ".\n";
  }
  else {
    output << "In station " << station << " stappen " << zitplaatsen-passagiers << " mensen op tram "
    << spoor << ".\n";
    getAlleTrams()->at(spoor)->setPassagiers(zitplaatsen);
    error << "ERROR: Maximum capaciteit ("<< zitplaatsen <<") tram "<< spoor
    <<" overschreden aan station " << station << ". Reeds " << passagiers
    << " passagiers op tram, " << opstappen << " mensen stappen op.\n";
  }
}

void MetroNet::moveAllePassengers(std::ostream& output, std::ostream& errors) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAllePassengers");
  for (auto& tram : alleTrams) {
    movePassengers(getAlleStations()->at(tram.second->getCurrentStation())->getNaam(), tram.first, output, errors);
  }
}

void MetroNet::writeToOutputStream(std::ostream& output) {
  REQUIRE(isConsistent(), "MetroNet is not consistent");
  for(auto mapIt = getAlleStations()->begin();
      mapIt != getAlleStations()->end();
      ++mapIt)
  {
    output << "Station " << mapIt->second->getNaam() << std::endl;
    output << "<- Station " << mapIt->second->getVorige() << std::endl;
    output << "-> Station " << mapIt->second->getVolgende() << std::endl;

    int spoor = mapIt->second->getSpoor();
    output << "Spoor " << spoor << ", "
            << (getAlleTrams()->at(spoor))->getZitplaatsen() << " zitplaatsen\n\n";
  }
}

void MetroNet::writeToASCII() {
  std::ofstream metroNetTXT;
  metroNetTXT.open ("_output/MetroNet.txt");
  writeToOutputStream(metroNetTXT);
  metroNetTXT.close();
}
