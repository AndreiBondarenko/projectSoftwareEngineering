#include "Station.h"
#include "DesignByContract.h"
#include <iostream>
#include <algorithm>
#include "MetroNet.h"

Station::Station()  {
  initCheck = this;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}

Station::Station(const std::string& naam):
  naam(naam)
{
  REQUIRE(naam != "", "naam must not be empty");
  initCheck = this;
  ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
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
    "Station wasn't initialized when calling isTramInStation");
  REQUIRE(spoor >= 0,
    "parameter spoor must be >= 0, when passed to isTramInStation");
	for (auto& it : tramInStation) {
		if (it.first.first == spoor && it.second) {
			return true;
		}
	}
	return false;
}

int Station::getTramInStation(const int spoor) const {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getTramInStation");
	REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
	REQUIRE(isTramInStation(spoor), "no tram in station when calling getTramInStation");
	for (auto& it : tramInStation) {
		if (it.second && it.first.first == spoor)
			return it.first.second;
	}
	return -1;
}

std::set<int> Station::getTramInStation() const {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getTramInStation");
	std::set<int> voertuigNrs;
	for (auto& it : tramInStation) {
		if (it.second)
			voertuigNrs.insert(it.first.second);
	}
	return voertuigNrs;
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
  REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
  vorige[spoor] = newVorige;
  ENSURE(getVorige(spoor) == newVorige,
    "setVorige post condition failure");
}

void Station::addVolgende(const int& spoor, const std::string& newVolgende) {
  REQUIRE(properlyInitialized(),
    "Station wasn't initialized when calling setVolgende");
  REQUIRE(newVolgende != "", "newVolgende must not be empty");
  REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
  volgende[spoor] = newVolgende;
  ENSURE(getVolgende(spoor) == newVolgende,
    "setVolgende post condition failure");
}

bool Station::setTramInStation(const int& spoor, const int voertuigNr, const bool& newTramInStation) {
  REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setTramInStation");
	REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
	REQUIRE(voertuigNr >= 0, "voertuigNr must be bigger or equal to zero");
	std::pair<int, int> tram = std::make_pair(spoor, voertuigNr);
	if (newTramInStation && isTramInStation(spoor)) {
		ENSURE(isTramInStation(spoor) != newTramInStation, "setTramInStation post condition failure");
		return false;
	}
	tramInStation[tram] = newTramInStation;
  ENSURE(isTramInStation(spoor) == newTramInStation, "setTramInStation post condition failure");
	return true;
}

bool Station::isInStation(std::string passagier) {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling isInStation");
	REQUIRE(passagier != "", "passagier must not be empty");
	return passagiers.find(passagier) != passagiers.end();
}

void Station::addPassagier(std::string passagier) {

	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling addPassagier");
	REQUIRE(passagier != "", "passagier must not be empty");
	REQUIRE(isInStation(passagier) == false, "passenger allready in Station");
	passagiers.insert(passagier);
	ENSURE(isInStation(passagier) == true, "addPassagier post condition failure");
}

void Station::removePassagier(std::string passagier) {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling removePassagier");
	REQUIRE(passagier != "", "passagier must not be empty");
	REQUIRE(isInStation(passagier) == true, "passenger not in Station");
	passagiers.erase(passagier);
	ENSURE(isInStation(passagier) == false, "removePassagier post condition failure");
}

void Station::movePassagiers(MetroNet& metronet, std::ostream& output) {
	REQUIRE(properlyInitialized(), "Station wasn't initialized when calling movePassagiers");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling movePassagiers");
	std::set<int> tramsInStation = getTramInStation();
	for (int tramInStation : tramsInStation) {
		Tram* tram = metronet.getTram(tramInStation);
		if (tram == nullptr) {
			return;
		}
		std::set<std::string> afstappen = tram->afstappenInHalte(metronet, naam);
		std::set<std::string>::iterator it;
		// afstappen
		for (std::string passagierName : afstappen) {
			Passagier* passagier = metronet.getPassagier(passagierName);
			passagiers.insert(passagierName);
			tram->removePassagier(passagierName);
			passagier->markAangekomen();
			output << passagierName << " (" << passagier->getHoeveelheid() << ") stapt uit in station " << naam << std::endl;
			if (tram->getAantalPassagiers() - passagier->getHoeveelheid() < 0) {
				output << passagierName << " (" << passagier->getHoeveelheid() << ") stapt uit in station " << naam << ", slechts "
					<< tram->getAantalPassagiers() << " passagiers aan boord." << std::endl;
				tram->setAantalPassagiers(0);
			}
			else {
				tram->setAantalPassagiers(tram->getAantalPassagiers() - passagier->getHoeveelheid());
			}
		}
		// opstappen
		for (it = passagiers.begin(); it != passagiers.end(); ) {
			Passagier* passagier = metronet.getPassagier(*it);
			if (passagier->getBeginStation() == naam &&
				tram->stoptInStation(metronet, passagier->getEindStation()) && 
				tram->stoptInStation(metronet, passagier->getBeginStation())) {
				if (tram->getAantalPassagiers() + passagier->getHoeveelheid() > tram->getZitplaatsen()) {
					output << passagier->getNaam() << " (" << passagier->getHoeveelheid() <<
						") kan niet meer op tram met voertuigNr " << tram->getVoertuigNr() << ", slechts " <<
						tram->getZitplaatsen() - tram->getAantalPassagiers() << " vrije plaatsen." << std::endl;
					++it;
				}
				else {
					tram->addPassagier(*it, metronet.getPassagier(*it)->getHoeveelheid());
					it = passagiers.erase(it);
					tram->setAantalPassagiers(tram->getAantalPassagiers() + passagier->getHoeveelheid());
					output << passagier->getNaam() << " (" << passagier->getHoeveelheid() <<
						") stapt op tram met voertuigNr " << tram->getVoertuigNr() << std::endl;
				}
			}
			else {
				++it;
			}
		}
	}
	ENSURE(metronet.isConsistent(), "movePassagiers made MetroNet inconsistent");
}
