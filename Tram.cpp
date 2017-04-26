#include "Tram.h"
#include "DesignByContract.h"
#include <iostream>

const int ticketPrijs = 2;

Tram::Tram()  {
	initCheck = this;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
Tram::Tram(const int lijnNr, const int zitplaatsen, const std::string& beginStation,
	const int snelheid) :
	lijnNr(lijnNr),
	zitplaatsen(zitplaatsen),
    snelheid(snelheid),
	beginStation(beginStation),
  currentStation(beginStation)
{
  REQUIRE(beginStation != "", "beginStation must not be empty");
  REQUIRE(lijnNr >= 0 , "lijnNr must be bigger or equal to zero");
  REQUIRE(zitplaatsen >= 0 , "zitplaatsen must be bigger or equal to zero");
  REQUIRE(snelheid >= 0 , "snelheid must be bigger or equal to zero");
	initCheck = this;
  ENSURE(properlyInitialized(),
    "constructor must end in properlyInitialized state");
}
Tram::~Tram() {
}

bool Tram::properlyInitialized() const{
	return initCheck == this;
}

int Tram::getLijnNr() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getLijnNr");
	return lijnNr;
}

int Tram::getZitplaatsen() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getZitplaatsen");
	return zitplaatsen;
}

std::string Tram::getType() const {
    REQUIRE(properlyInitialized(),
      "Tram wasn't initialized when calling getType");
    return type;
}

std::string Tram::getBeginStation() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getBeginStation");
	return beginStation;
}

std::string Tram::getCurrentStation() const {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getCurrentStation");
  return currentStation;
}

int Tram::getAantalPassagiers() const {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getAantalPassagiers");
    return aantalPassagiers;
}

int Tram::getSnelheid() const {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getSnelheid");
	return snelheid;
}

int Tram::getVoertuigNr() const {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling getVoertuigNr");
  return voertuigNr;
}

void Tram::setLijnNr(const int newLijnNr) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setLijnNr");
  REQUIRE(newLijnNr >= 0 , "newLijnNr must be bigger or equal to zero");

	lijnNr = newLijnNr;
	ENSURE(getLijnNr() == newLijnNr, "setLijnNr post condition failure");
}

void Tram::setZitplaatsen(const int newZitplaatsen) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setZitplaatsen");
  REQUIRE(newZitplaatsen >= 0 ,
    "newZitplaatsen must be bigger or equal to zero");
	zitplaatsen = newZitplaatsen;
	ENSURE(getZitplaatsen() == newZitplaatsen,
    "setZitplaatsen post condition failure");
}

void Tram::setType(const std::string &newType) {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setType");
  REQUIRE(newType != "",
    "newType must not be empty");
  type = newType;
  ENSURE(getType() == newType,
    "setType post condition failure");
}

void Tram::setBeginStation(const std::string & newBeginStation) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setBeginStation");
  REQUIRE(newBeginStation != "", "newBeginStation must not be empty");
	beginStation = newBeginStation;
	ENSURE(getBeginStation() == newBeginStation,
    "setBeginStation post condition failure");
}

void Tram::setCurrentStation(const std::string &newCurrentStation) {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setCurrentStation");
  REQUIRE(newCurrentStation != "", "newCurrentStation must not be empty");
  currentStation = newCurrentStation;
  ENSURE(getCurrentStation() == newCurrentStation,
    "setCurrentStation post condition failure");

}

void Tram::setSnelheid(const int newSnelheid) {
	REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setSnelheid");
  REQUIRE(newSnelheid >= 0 , "newSnelheid must be bigger or equal to zero");
	snelheid = newSnelheid;
	ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
}

void Tram::setAantalPassagiers(const int newAantalPassagiers) {
  REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setAantalPassagiers");
  REQUIRE(newAantalPassagiers >= 0 , "newPassagiers must be bigger or equal to zero");
  aantalPassagiers = newAantalPassagiers;
  ENSURE(getAantalPassagiers() == newAantalPassagiers, "setAantalPassagiers post condition failure");
}

void Tram::setVoertuigNr(const int newVoertuigNr) {
  REQUIRE(properlyInitialized(),
    "Tram wasn't initialized when calling setVoertuigNr");
  REQUIRE(newVoertuigNr >= 0 ,
    "newVoertuigNr must be bigger or equal to zero");
  voertuigNr = newVoertuigNr;
  ENSURE(getVoertuigNr() == newVoertuigNr,
    "setVoertuigNr post condition failure");
}

bool Tram::isInTram(std::string passagier) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setVoertuigNr");
	REQUIRE(passagier != "", "passagier must not be empty");
	return passagiers.find(passagier) != passagiers.end();
}

void Tram::addPassagier(std::string passagier, int aantal) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setVoertuigNr");
	REQUIRE(passagier != "", "passagier must not be empty");
	REQUIRE(isInTram(passagier) == false, "passenger allready in Tram");
	passagiers.insert(passagier);
  setOmzet(getOmzet() + ticketPrijs);
	ENSURE(isInTram(passagier) == true, "addPassagier post condition failure");
}

void Tram::removePassagier(std::string passagier) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setVoertuigNr");
	REQUIRE(passagier != "", "passagier must not be empty");
	REQUIRE(isInTram(passagier) == true, "passenger not in Tram");
	passagiers.erase(passagier);
	ENSURE(isInTram(passagier) == false, "addPassagier post condition failure");
}

std::set<std::string> Tram::afstappenInHalte(MetroNet& metronet, std::string station) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling afstappenInHalte");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling afstappenInHalte");
	REQUIRE(station != "", "station must not be empty");
	std::set<std::string> afstappen;
	for (std::string passagierName : passagiers) {
		Passagier* passagier = metronet.getPassagier(passagierName);
		if (passagier->getEindStation() == station) {
			afstappen.insert(passagierName);
		}
	}
	return afstappen;
}

bool Tram::stoptInStation(MetroNet& metronet, std::string station) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling afstappenInHalte");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling afstappenInHalte");
	REQUIRE(station != "", "station must not be empty");
	std::string nextStation = metronet.getStation(currentStation)->getVolgende(lijnNr);
	while (nextStation != currentStation) {
		if (nextStation == station) {
			if (type == "Albatros" && metronet.getStation(station)->getType() != "Metrostation")
				return false;
			return true;
		}
		nextStation = metronet.getStation(nextStation)->getVolgende(lijnNr);
	}
	return false;
}

int Tram::getOmzet() const {
  REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getOmzet");
  return omzet;
}

void Tram::setOmzet(const int newOmzet) {
  REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setOmzet");
  REQUIRE(newOmzet >= 0 , "newOmzet must be bigger or equal to zero");
  omzet = newOmzet;
  ENSURE(getOmzet() == newOmzet, "setOmzet post condition failure");
}

void Tram::moveTram(MetroNet& metronet, std::ostream& output) {
	REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling moveTram");
	REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling moveTram");
	Station* nextStation = metronet.getStation(metronet.getStation(currentStation)->getVolgende(lijnNr));
	while (!stoptInStation(metronet, nextStation->getNaam())) {
		nextStation = metronet.getStation(nextStation->getVolgende(lijnNr));
	}
	if (!nextStation->isTramInStation(lijnNr)) {
		metronet.getStation(currentStation)->setTramInStation(lijnNr, voertuigNr, false);
		nextStation->setTramInStation(lijnNr, voertuigNr, true);
		output
			<< "Tram #" << voertuigNr << " op spoor " << lijnNr << " reed van station "
			<< currentStation << " naar station " << nextStation->getNaam() << "." << std::endl;
		currentStation = nextStation->getNaam();
	}
	else {
		output
			<< "Tram #" << voertuigNr << " op spoor " << lijnNr << " wachtte in station "
			<< currentStation << ", want station " << nextStation->getNaam() 
			<< " was bezet door Tram #" << nextStation->getTramInStation(lijnNr) << "." << std::endl;
	}
	ENSURE(metronet.isConsistent(), "moveTram made MetroNet inconsistent");
}