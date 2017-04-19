#include "MetroNet.h"
#include "tinyxml.h"
#include "DesignByContract.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

MetroNet::MetroNet()  {
  initCheck = this;
	alleStations.clear();
	alleTrams.clear();
	alleSporen.clear();
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
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling isConsistent");
  // elk station is verbonden met een voorgaand en een volgend station
  // voor elk spoor
  for(auto station : alleStations) {
    std::string vorige = station.second->getVorige();
    std::string volgende = station.second->getVolgende();
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

Station* MetroNet::getStation(std::string naam) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getStation");
	if (alleStations.find(naam) == alleStations.end()) {
		return nullptr;
	}
  return alleStations[naam];
}

Tram* MetroNet::getTram(int spoor) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getTram");
	if (alleTrams.find(spoor) == alleTrams.end())
		return nullptr;
  return alleTrams[spoor];
}

Passagier* MetroNet::getPassagier(std::string naam) {
	REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getPassagier");
	return allePassagiers[naam];
}

void MetroNet::addStation(Station* newStation) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addStation");
  REQUIRE(getStation(newStation->getNaam()) == nullptr, "This MetroNet already contains a station with this name");
  alleSporen.insert(newStation->getSpoor());
  alleStations[newStation->getNaam()] = newStation;
  ENSURE(getStation(newStation->getNaam()) == newStation, "addStation post condition failure");
}

void MetroNet::addTram(Tram* newTram) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addTram");
  REQUIRE(getTram(newTram->getLijnNr()) == nullptr, "This MetroNet already contains a Tram with this lijnNr");
  alleTrams[newTram->getLijnNr()] = newTram;
  alleStations[newTram->getBeginStation()]->setTramInStation(true);
  ENSURE(getTram(newTram->getLijnNr()) == newTram, "addTram post condition failure");
  ENSURE(getStation(newTram->getBeginStation())->isTramInStation(), "addTram post condition failure");
}

void MetroNet::addPassagier(Passagier* newPassagier) {
	REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addPassagier");
	REQUIRE(getPassagier(newPassagier->getNaam()) == nullptr, "This MetroNet allready contains a passenger with this name");
	allePassagiers[newPassagier->getNaam()] = newPassagier;
	ENSURE(getPassagier(newPassagier->getNaam()) == newPassagier, "addPassagier post condition failure");
}

void MetroNet::moveTram(std::string station, int spoor, std::ostream& output) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveTrams");
  REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  REQUIRE(station != "", "station must not be empty");
  std::string currentStation = getTram(spoor)->getCurrentStation();
  getStation(currentStation)->setTramInStation(false);
  getTram(spoor)->setCurrentStation(station);
  getStation(station)->setTramInStation(true);
  output << "Tram " << spoor << " reed van station " << currentStation << " naar station " << station << ".\n";
  ENSURE(getStation(station)->isTramInStation(), "moveTram post condition failure");
  ENSURE(station == getTram(spoor)->getCurrentStation(), "moveTram post condition failure");
  ENSURE(isConsistent(), "moveTram made MetroNet inconsistent");
}

void MetroNet::moveAlleTrams(std::ostream& output) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAlleTrams");
  for (auto& tram : alleTrams) {
    moveTram(getStation(tram.second->getCurrentStation())->getVolgende(), tram.first, output);
  }
  ENSURE(isConsistent(), "moveAlleTrams made MetroNet inconsistent");
}

void MetroNet::movePassengers(std::string station, int spoor, std::ostream& output, std::ostream& error) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling movePassengers");
  REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  REQUIRE(station != "", "station must not be empty");
  REQUIRE(getTram(spoor)->getCurrentStation() == station, "Tram not in given station");
  REQUIRE(getStation(station)->isTramInStation(), "Station is empty");
  const int afstappen = getStation(station)->getAfstappen();
  const int opstappen = getStation(station)->getOpstappen();
  int passagiers = getTram(spoor)->getPassagiers();
  const int zitplaatsen = getTram(spoor)->getZitplaatsen();
  if(afstappen <= passagiers){
    getTram(spoor)->setPassagiers(passagiers-afstappen);
    output << "In station " << station << " stappen " << afstappen << " mensen af tram "
    << spoor << ".\n";
  }
  else {
    output << "In station " << station << " stappen " << passagiers << " mensen af tram "
    << spoor << ".\n";
    getTram(spoor)->setPassagiers(0);
    error << "ERROR: Aan station " << station << " stappen " << afstappen
    << " mensen af tram " << spoor << ". Slechts " << passagiers << " mensen op de tram.\n";
  }
  passagiers = getTram(spoor)->getPassagiers();
  if(passagiers + opstappen <= zitplaatsen){
    getTram(spoor)->setPassagiers(passagiers+opstappen);
    output << "In station " << station << " stappen " << opstappen << " mensen op tram "
    << spoor << ".\n";
  }
  else {
    output << "In station " << station << " stappen " << zitplaatsen-passagiers << " mensen op tram "
    << spoor << ".\n";
    getTram(spoor)->setPassagiers(zitplaatsen);
    error << "ERROR: Maximum capaciteit ("<< zitplaatsen <<") tram "<< spoor
    <<" overschreden aan station " << station << ". Reeds " << passagiers
    << " passagiers op tram, " << opstappen << " mensen stappen op.\n";
  }
}


void MetroNet::moveAllePassengers(std::ostream& output, std::ostream& errors) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAllePassengers");
  for (auto& tram : alleTrams) {
    movePassengers(getStation(tram.second->getCurrentStation())->getNaam(), tram.first, output, errors);
  }
}

void MetroNet::writeToOutputStream(std::ostream& output) {
  REQUIRE(isConsistent(), "MetroNet is not consistent");
  for(auto mapIt = alleStations.begin();
      mapIt != alleStations.end();
      ++mapIt)
  {
    output << "Station " << mapIt->second->getNaam() << std::endl;
    output << "<- Station " << mapIt->second->getVorige() << std::endl;
    output << "-> Station " << mapIt->second->getVolgende() << std::endl;

    int spoor = mapIt->second->getSpoor();
    output << "Spoor " << spoor << ", "
            << (alleTrams.at(spoor))->getZitplaatsen() << " zitplaatsen\n\n";
  }
}

void MetroNet::writeToASCII() {
  std::ofstream metroNetTXT;
  metroNetTXT.open ("_output/MetroNet.txt");
  writeToOutputStream(metroNetTXT);
  metroNetTXT.close();
}
