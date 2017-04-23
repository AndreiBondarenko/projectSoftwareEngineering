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
  // REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling isConsistent");
  // // elk station is verbonden met een voorgaand en een volgend station
  // // voor elk spoor
  // for(auto station : alleStations) {
  //   std::string vorige = station.second->getVorige();
  //   std::string volgende = station.second->getVolgende();
  //   if (alleStations.find(vorige) == alleStations.end() ||
  //       alleStations.find(volgende) == alleStations.end()) {
  //     return false;
  //   }
  // }
  // // er bestaan geen trams met een lijn nummer dat niet overeenkomt met een
  // // spoor in een station
  // // het beginstation van een tram een geldig station in het metronet is
  // for(auto mapIt = alleTrams.begin(); mapIt != alleTrams.end(); ++mapIt) {
  //   int lijnNr = mapIt->second->getLijnNr();
  //   std::string beginStation = mapIt->second->getBeginStation();
  //   if (alleSporen.find(lijnNr) == alleSporen.end()) {
  //     return false;
  //   }
  //   if (alleStations.find(beginStation) == alleStations.end()) {
  //     return false;
  //   }
  // }
  // // er geen sporen zijn waarvoor geen tram bestaat
  // for(auto setIt = alleSporen.begin(); setIt != alleSporen.end(); ++setIt) {
  //   int spoor = *setIt;
  //   if (alleTrams.find(spoor) == alleTrams.end()) {
  //     return false;
  //   }
  // }
  // // elk spoor maximaal een keer door elk station komt ???????????????????????
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
  for(int x: newStation->getSporen()) {
    alleSporen.insert(x);
  }
  alleStations[newStation->getNaam()] = newStation;
  ENSURE(getStation(newStation->getNaam()) == newStation, "addStation post condition failure");
}

void MetroNet::addTram(Tram* newTram) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addTram");
  REQUIRE(getTram(newTram->getVoertuigNr()) == nullptr, "This MetroNet already contains a Tram with this lijnNr");
  alleTrams[newTram->getVoertuigNr()] = newTram;
  alleStations[newTram->getBeginStation()]->setTramInStation(newTram->getLijnNr(), true);
  ENSURE(getTram(newTram->getVoertuigNr()) == newTram, "addTram post condition failure");
  ENSURE(getStation(newTram->getBeginStation())->isTramInStation(newTram->getLijnNr()), "addTram post condition failure");
}

void MetroNet::addPassagier(Passagier* newPassagier) {
	REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addPassagier");
	REQUIRE(getPassagier(newPassagier->getNaam()) == nullptr, "This MetroNet allready contains a passenger with this name");
	allePassagiers[newPassagier->getNaam()] = newPassagier;
	ENSURE(getPassagier(newPassagier->getNaam()) == newPassagier, "addPassagier post condition failure");
}

void MetroNet::moveTram(std::string station, int voertuigNr, std::ostream& output) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveTrams");
  REQUIRE(voertuigNr >= 0 , "spoor must be bigger or equal to zero");
  REQUIRE(station != "", "station must not be empty");
  Tram* tram = getTram(voertuigNr);
  std::string currentStation = tram->getCurrentStation();
  int lijnNr = tram ->getLijnNr();
  getStation(currentStation)->setTramInStation(lijnNr, false);
  tram->setCurrentStation(station);
  getStation(station)->setTramInStation(lijnNr, true);
  output << "Tram #" << voertuigNr << "op spoor "<< lijnNr << " reed van station " << currentStation << " naar station " << station << ".\n";
  ENSURE(getStation(station)->isTramInStation(lijnNr), "moveTram post condition failure");
  ENSURE(station == getTram(voertuigNr)->getCurrentStation(), "moveTram post condition failure");
  ENSURE(isConsistent(), "moveTram made MetroNet inconsistent");
}

void MetroNet::moveAlleTrams(std::ostream& output) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAlleTrams");
  for (auto& tram : alleTrams) {
    int voeruigNr = tram.first;
    int lijnNr = tram.second->getLijnNr();
    std::string currentStation = tram.second->getCurrentStation();
    std::string nextStation = getStation(currentStation)->getVolgende(lijnNr);
    moveTram(nextStation, voeruigNr, output);
  }
  ENSURE(isConsistent(), "moveAlleTrams made MetroNet inconsistent");
}

void MetroNet::movePassengers(std::string station, int voeruigNr, std::ostream& output, std::ostream& error) {
  //
  // Voorlopig weggecomment, was ni zeker of al klaar en heb er zelf wa in zitten knoeien
  //
  // REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling movePassengers");
  // REQUIRE(voeruigNr >= 0 , "voeruigNr must be bigger or equal to zero");
  // REQUIRE(station != "", "station must not be empty");
  // REQUIRE(getTram(voeruigNr)->getCurrentStation() == station, "Tram not in given station");
  // REQUIRE(getStation(station)->isTramInStation(getTram(voeruigNr)->getLijnNr()), "Station is empty");
  // Tram* tram = getTram(voeruigNr);
  // const int afstappen = getStation(station)->getAfstappen();
  // const int opstappen = getStation(station)->getOpstappen();
  // int passagiers = tram->getPassagierCount();
  // const int zitplaatsen = tram->getZitplaatsen();
  // if(afstappen <= passagiers){
  //   tram->setPassagiers(passagiers-afstappen);
  //   output << "In station " << station << " stappen " << afstappen << " mensen af tram "
  //   << spoor << ".\n";
  // }
  // else {
  //   output << "In station " << station << " stappen " << passagiers << " mensen af tram "
  //   << spoor << ".\n";
  //   getTram(spoor)->setPassagiers(0);
  //   error << "ERROR: Aan station " << station << " stappen " << afstappen
  //   << " mensen af tram " << spoor << ". Slechts " << passagiers << " mensen op de tram.\n";
  // }
  // passagiers = getTram(spoor)->getPassagiers();
  // if(passagiers + opstappen <= zitplaatsen){
  //   getTram(spoor)->setPassagiers(passagiers+opstappen);
  //   output << "In station " << station << " stappen " << opstappen << " mensen op tram "
  //   << spoor << ".\n";
  // }
  // else {
  //   output << "In station " << station << " stappen " << zitplaatsen-passagiers << " mensen op tram "
  //   << spoor << ".\n";
  //   getTram(spoor)->setPassagiers(zitplaatsen);
  //   error << "ERROR: Maximum capaciteit ("<< zitplaatsen <<") tram "<< spoor
  //   <<" overschreden aan station " << station << ". Reeds " << passagiers
  //   << " passagiers op tram, " << opstappen << " mensen stappen op.\n";
  // }
}


void MetroNet::moveAllePassengers(std::ostream& output, std::ostream& errors) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAllePassengers");
  for (auto& tram : alleTrams) {
    movePassengers(getStation(tram.second->getCurrentStation())->getNaam(), tram.second->getVoertuigNr(), output, errors);
  }
}

void MetroNet::writeToOutputStream(std::ostream& output) {
  REQUIRE(isConsistent(), "MetroNet is not consistent");
  output << "--== STATIONS ==--" << std::endl;
  for(auto stationIt = alleStations.begin(); stationIt != alleStations.end(); stationIt++) {
    output << "-> Station " << stationIt->first << std::endl;
    output << "wachtende passagiers:" << std::endl;
    for(auto passengerIt = allePassagiers.begin(); passengerIt != allePassagiers.end(); passengerIt++) {
      if (stationIt->second->isInStation(passengerIt->first)) {
        Passagier* info = passengerIt->second;
        output
          << "* "
          << info->getNaam()
          << ", "
          << info->getHoeveelheid()
          << " mensen, reist naar station "
          << info->getEindStation()
          << std::endl
          << std::endl;
      }
    }
    output << std::endl;
  }
  output << std::endl << "--== TRAMS ==--" << std::endl;
  for(auto tramIt = alleTrams.begin(); tramIt != alleTrams.end(); tramIt++) {
    Tram* info = tramIt->second;
    output
      << "Tram " << info->getLijnNr() << " nr " << info->getVoertuigNr() << std::endl
      << "zitplaatsen: " << info->getZitplaatsen() << std::endl
      << "snelheid: " << info->getSnelheid() << std::endl
      << "huidige station: " << info->getCurrentStation() << std::endl
      << "reizende passagiers:" << std::endl;
    for(auto passengerIt = allePassagiers.begin(); passengerIt != allePassagiers.end(); passengerIt++) {
      if (info->isInTram(passengerIt->first)) {
        Passagier* info = passengerIt->second;
        output
          << "* "
          << info->getNaam()
          << ", "
          << info->getHoeveelheid()
          << " mensen, reist naar station "
          << info->getEindStation()
          << std::endl;
      }
    }
    output << std::endl;
  }
}

void MetroNet::drawToOutputStream(std::ostream &output) {
  for(auto spoorIt = alleSporen.begin(); spoorIt != alleSporen.end(); spoorIt++) {
    output << "Spoor " << *spoorIt << " :" << std::endl;
    std::string route = "=";
    std::string trams = " ";
    std::string firstStop;
    std::string current;
    for(auto stationIt = alleStations.begin(); stationIt != alleStations.end(); stationIt++) {
      try {
        firstStop = stationIt->second->getVolgende(*spoorIt);
        route.append(firstStop);
        if(stationIt->second->isTramInStation(*spoorIt)) {
          trams.append("T");
        }
        else {
          trams.append(" ");
        }
        break;
      }
      catch(std::out_of_range e) {
        continue;
      }
    }
    current = getStation(firstStop)->getVolgende(*spoorIt);
    while (current != firstStop) {
      route.append("==");
      route.append(current);
      trams.append("  ");
      if(getStation(current)->isTramInStation(*spoorIt)) {
        trams.append("T");
      }
      else {
        trams.append(" ");
      }
      current = getStation(current)->getVolgende(*spoorIt);
    }
    route.append("=");
    trams.append(" ");
    output << route << std::endl;
    output << trams << std::endl << std::endl;
  }
}

void MetroNet::writeToASCII() {
  std::ofstream metroNetTXT;
  metroNetTXT.open ("_output/MetroNet.txt");
  writeToOutputStream(metroNetTXT);
  metroNetTXT.close();
}
