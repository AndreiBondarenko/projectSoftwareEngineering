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

bool MetroNet::isConsistent() {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling isConsistent");
	// elk station is verbonden met een voorgaand en een volgend station
  // voor elk spoor
	for (auto& station : alleStations) {
		std::set<int> sporen = station.second->getSporen();
		for (int lijnNr : sporen) {
			if (getStation(station.second->getVolgende(lijnNr)) == nullptr ||
					getStation(station.second->getVorige(lijnNr)) == nullptr) {
				return false;
			}
		}
	}
  // er bestaan geen trams met een lijn nummer dat niet overeenkomt met een
  // spoor in een station
  // het beginstation van een tram een geldig station in het metronet is
	for (auto& tram : alleTrams) {
		if (alleSporen.find(tram.second->getLijnNr()) == alleSporen.end() ||
				getStation(tram.second->getBeginStation()) == nullptr) {
			return false;
		}
	}
  // er geen sporen zijn waarvoor geen tram bestaat
	for (int lijnNr : alleSporen) {
		bool foundTram = false;
		for (auto& tram : alleTrams) {
			if (tram.second->getLijnNr() == lijnNr) {
				foundTram = true;
				break;
			}
		}
		if (!foundTram) {
			return false;
		}
	}
	// iedere passagier ofwel in een station, ofwel in een tram zit
	// een passagier zit niet in meerdere trams/stations
	for (const auto& it : allePassagiers) {
		std::string passagier = it.first;
		int count = 0;
		for (const auto& tramIt : alleTrams) {
			if (tramIt.second->isInTram(passagier))
				count++;
		}
		for (const auto& stationIt : alleStations) {
			if (stationIt.second->isInStation(passagier))
				count++;
		}
		if (count != 1) {
			return false;
		}
	}
	// begin- en eindStation van iedere passagier bestaat
	for (const auto& it : allePassagiers) {
		Passagier* passagier = it.second;
		if (alleStations.find(passagier->getBeginStation()) == alleStations.end() ||
			alleStations.find(passagier->getEindStation()) == alleStations.end()) {
			return false;
		}
	}
  return true;
}

Station* MetroNet::getStation(std::string naam) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getStation");
	if (alleStations.find(naam) == alleStations.end()) {
		return nullptr;
	}
  return alleStations[naam];
}

Tram* MetroNet::getTram(int voertuigNr) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getTram");
	if (alleTrams.find(voertuigNr) == alleTrams.end())
		return nullptr;
  return alleTrams[voertuigNr];
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
  alleStations[newTram->getBeginStation()]->setTramInStation(newTram->getLijnNr(), newTram->getVoertuigNr(), true);
  ENSURE(getTram(newTram->getVoertuigNr()) == newTram, "addTram post condition failure");
  ENSURE(getStation(newTram->getBeginStation())->isTramInStation(newTram->getLijnNr()), "addTram post condition failure");
}

void MetroNet::addPassagier(Passagier* newPassagier) {
	REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addPassagier");
	REQUIRE(getPassagier(newPassagier->getNaam()) == nullptr, "This MetroNet allready contains a passenger with this name");
	allePassagiers[newPassagier->getNaam()] = newPassagier;
	ENSURE(getPassagier(newPassagier->getNaam()) == newPassagier, "addPassagier post condition failure");
}

void MetroNet::moveAlleTrams(std::ostream& output) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAlleTrams");
  for (auto& tram : alleTrams) {
    tram.second->moveTram(*this, output);
  }
  ENSURE(isConsistent(), "moveAlleTrams made MetroNet inconsistent");
}

void MetroNet::moveAllePassengers(std::ostream& output, std::ostream& errors) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAllePassengers");
  for (auto& station : alleStations) {
		station.second->movePassagiers(*this, output, errors);
  }
}

void MetroNet::runSimulation(std::ostream &output, std::ostream &errors) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling runSimulation");
	bool simulationCompleted = false;
	for (int i = 1; !simulationCompleted; i++) {
		output << i << "." << std::endl;
    simulationCompleted = true;
    moveAllePassengers(output, errors);
		moveAlleTrams(output);
		output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    for(auto mapIt = allePassagiers.begin(); mapIt != allePassagiers.end(); mapIt++) {
      if (!mapIt->second->isAangekomen()) {
        simulationCompleted = false;
        break;
      }
    }
  }
  ENSURE(isConsistent(), "runSimulation made MetroNet inconsistent");
}

void MetroNet::writeToOutputStream(std::ostream& output) {
  REQUIRE(isConsistent(), "MetroNet is not consistent");
  output << "--== STATIONS ==--" << std::endl;
  for(auto stationIt = alleStations.begin(); stationIt != alleStations.end(); stationIt++) {
    output << "-> Station " << stationIt->first << std::endl;
    output << "wachtende passagiers:" << std::endl;
    for(auto passengerIt = allePassagiers.begin(); passengerIt != allePassagiers.end(); passengerIt++) {
      if (stationIt->second->isInStation(passengerIt->first) && passengerIt->second->getBeginStation() == stationIt->first) {
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
		output << "gearriveerde passagiers:" << std::endl;
		for (auto passengerIt = allePassagiers.begin(); passengerIt != allePassagiers.end(); passengerIt++) {
			if (stationIt->second->isInStation(passengerIt->first) && passengerIt->second->getEindStation() == stationIt->first) {
				Passagier* info = passengerIt->second;
				output
					<< "* "
					<< info->getNaam()
					<< ", "
					<< info->getHoeveelheid()
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
      << "omzet: " << info->getOmzet() << std::endl
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
		output
			<< "vrije zitplaatsen: " << info->getZitplaatsen() - info->getAantalPassagiers() << std::endl
			<< std::endl;
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
      if (stationIt->second->getSporen().count(*spoorIt) == 1) {
        firstStop = stationIt->first;
        route.append(firstStop);
        if(stationIt->second->isTramInStation(*spoorIt)) {
          trams.append("T");
        }
        else {
          trams.append(" ");
        }
        break;
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
