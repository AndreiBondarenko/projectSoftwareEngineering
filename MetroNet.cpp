#include "MetroNet.h"
#include "tinyxml.h"
#include "DesignByContract.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

const int MAXAANTALLOOPS = 1000;
const int MAX_CHARACTERS = 120;

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
	for (auto it = allePassagiers.begin(); it != allePassagiers.end(); ++it) {
		delete it->second;
	}
  alleStations.clear();
  alleTrams.clear();
  alleSporen.clear();
	allePassagiers.clear();
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
	// begin- en eindStation van iedere passagier bestaat, en ligt op eenzelfde spoor
	for (const auto& it : allePassagiers) {
		Passagier* passagier = it.second;
		if (alleStations.find(passagier->getBeginStation()) == alleStations.end() ||
			alleStations.find(passagier->getEindStation()) == alleStations.end()) {
			return false;
		}
		bool foundEindStation = false;
		for (int lijnNr : getStation(passagier->getBeginStation())->getSporen()) {
			std::set<int> eindSporen = getStation(passagier->getEindStation())->getSporen();
			if (eindSporen.find(lijnNr) != eindSporen.end()) {
				foundEindStation = true;
				break;
			}
		}
		if (!foundEindStation) {
			return false;
		}
	}
  return true;
}

Station* MetroNet::getStation(std::string naam) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getStation");
  REQUIRE(naam != "", "naam must not be empty");
	if (alleStations.find(naam) == alleStations.end()) {
		return nullptr;
	}
  return alleStations[naam];
}

Tram* MetroNet::getTram(int voertuigNr) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getTram");
  REQUIRE(voertuigNr >= 0, "voertuigNr must be greater or equal to zero");
	if (alleTrams.find(voertuigNr) == alleTrams.end())
		return nullptr;
  return alleTrams[voertuigNr];
}

Passagier* MetroNet::getPassagier(std::string naam) {
	REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getPassagier");
	REQUIRE(naam != "", "naam must not be empty");
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
  REQUIRE(getTram(newTram->getVoertuigNr()) == nullptr, "This MetroNet already contains a Tram with this voertuigNr");
	REQUIRE(getStation(newTram->getBeginStation())->isTramInStation(newTram->getLijnNr()) == false, "BeginStation of newTram isn't empty");
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

void MetroNet::moveAllePassengers(std::ostream& output) {
  REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAllePassengers");
  for (auto& station : alleStations) {
		station.second->movePassagiers(*this, output);
  }
}

void MetroNet::runSimulation(std::ostream &output, const bool live) {
	REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling runSimulation");
  if(live) {
    output << "BEGINSITUATIE:" << std::endl << std::endl;
    writeToOutputStream(output);
    output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  }
	bool simulationCompleted = false;
	int steps = 0;
	for (int i = 1; !simulationCompleted; i++) {
		if (i == MAXAANTALLOOPS) {
			output << "MetroNetSimulation stopped. Infinite loop occured." << std::endl;
			break;
		}
    if (live)
		{
			if (steps == 0)
			{
				while (true)
				{
					output << "Druk op ENTER om verder te gaan of:\n- geef \"-o\" in voor een overzicht\n- geef \"-v\" in voor een visuele impressie\n- geef het aantal stappen dat je verder wil gaan in\nResponse: ";
					std::string input;
					getline(std::cin, input);
					output << std::endl;
					if (input.empty())  break;
					else if (input == "-o") writeToOutputStream(output);
					else if (input == "-v") drawToOutputStream(output);
					try {
						steps = std::stoi(input);
						break;
					}
					catch (const std::exception&) { continue; }
				}
			}
			else --steps;
		}
		output << i << "." << std::endl;
		simulationCompleted = true;
		moveAlleTrams(output);
		moveAllePassengers(output);
		output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		for (auto mapIt = allePassagiers.begin(); mapIt != allePassagiers.end(); mapIt++) {
			if (!mapIt->second->isAangekomen()) {
				simulationCompleted = false;
				break;
			}
		}
		if (simulationCompleted && live)
		{
      while (true) {
        output << "Wilt u een overzicht van de eindsituatie tonen?\n- geef \"-o\" in voor een overzicht\n- geef \"-v\" in voor een visuele impressie\n- druk op ENTER om af te sluiten\nResponse: ";
        std::string input;
        getline(std::cin, input);
        output << std::endl;
        if (input.empty())  break;
        else if (input == "-o") writeToOutputStream(output);
        else if (input == "-v") drawToOutputStream(output);
      }
		}

	}
	ENSURE(isConsistent(), "runSimulation made MetroNet inconsistent");
}

void MetroNet::writeToOutputStream(std::ostream& output) {
  REQUIRE(isConsistent(), "MetroNet is not consistent");
  output << "--== STATIONS ==--" << std::endl;
  for(auto stationIt = alleStations.begin(); stationIt != alleStations.end(); stationIt++) {
    output << "-> Station " << stationIt->first;
    if(stationIt->second->albatrosCanStop()) output << " - Metro Station";
    else output << " - Halte";
    output << std::endl << "wachtende passagiers:" << std::endl;
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
	for (auto spoorIt = alleSporen.begin(); spoorIt != alleSporen.end(); spoorIt++) {
		output << "Spoor " << *spoorIt << " :" << std::endl;
		std::vector<std::string> routeVec;
		std::vector<std::string> tramVec;
		std::string route = "=";
		std::string trams = " ";
		std::string firstStop;
		std::string current;
		for (auto stationIt = alleStations.begin(); stationIt != alleStations.end(); stationIt++) {
			if (stationIt->second->getSporen().count(*spoorIt) == 1) {
				firstStop = stationIt->first;
				route.append(firstStop);
				if (stationIt->second->isTramInStation(*spoorIt)) {
					trams.append("T");
					for (unsigned int i = 0; i < stationIt->second->getNaam().length() - 1; i++) {
						trams.append(" ");
					}
				}
				else {
					for (unsigned int i = 0; i < stationIt->second->getNaam().length(); i++) {
						trams.append(" ");
					}
				}
				break;
			}
		}
		current = getStation(firstStop)->getVolgende(*spoorIt);
		while (current != firstStop) {
			if (route.length() < MAX_CHARACTERS) {
				route.append("==");
				route.append(current);
				trams.append("  ");
			}
			else {
				route.append("=");
				routeVec.push_back(route);
				route = "=";
				route.append(current);
				trams.append("  ");
				tramVec.push_back(trams);
				trams = " ";
			}
			if (getStation(current)->isTramInStation(*spoorIt)) {
				trams.append("T");
				for (unsigned int i = 0; i < getStation(current)->getNaam().length() - 1; i++) {
					trams.append(" ");
				}
			}
			else {
				for (unsigned int i = 0; i < getStation(current)->getNaam().length(); i++) {
					trams.append(" ");
				}
			}
			current = getStation(current)->getVolgende(*spoorIt);
			
		}
		route.append("=");
		trams.append(" ");
		routeVec.push_back(route);
		tramVec.push_back(trams);
		for (unsigned int i = 0; i < routeVec.size(); i++) {
			output << routeVec[i] << std::endl;
			output << tramVec[i] << std::endl;
		}
		output << std::endl;
	}
}

void MetroNet::writeToASCII() {
  std::ofstream metroNetTXT;
  metroNetTXT.open ("_output/MetroNet.txt");
  writeToOutputStream(metroNetTXT);
  metroNetTXT.close();
}
