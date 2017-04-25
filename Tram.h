#ifndef INC_TRAM_H
#define INC_TRAM_H
#pragma once

#include <string>
#include <set>
#include "MetroNet.h"

class MetroNet;

class Tram {
private:
  Tram* initCheck;
  int lijnNr;
  int voertuigNr;
  int zitplaatsen;
  int snelheid;
  std::string type;
  std::string beginStation;
  std::string currentStation;
  std::set<std::string> passagiers;
  int aantalPassagiers;
  int omzet = 0;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(); // default
  /**
  \n REQUIRE(beginStation != "", "newBeginStation must not be empty");
  \n REQUIRE(lijnNr >= 0 , "lijnNr must be bigger or equal to zero");
  \n REQUIRE(zitplaatsen >= 0 , "zitplaatsen must be bigger or equal to zero");
  \n REQUIRE(snelheid >= 0 , "snelheid must be bigger or equal to zero");
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(const int lijnNr, const int zitplaatsen, const std::string& beginStation,
	  const int snelheid); // full

  // DESTRUCTOR
  ~Tram();

  // INITIALIZATION CHECK
  bool properlyInitialized() const;

  // GETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getLijnNr");
  */
  int getLijnNr() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getZitplaatsen");
  */
  int getZitplaatsen() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getType");
  */
  std::string getType() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getBeginStation");
  */
  std::string getBeginStation() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  */
  std::string getCurrentStation() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
  */
  int getSnelheid() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getAantalPassagiers");
  */
  int getAantalPassagiers() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getVoertuigNr");
  */
  int getVoertuigNr() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getOmzet");
  */
  int getOmzet() const;

  // SETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setLijnNr");
  \n REQUIRE(newLijnNr >= 0 , "newLijnNr must be bigger or equal to zero");
  \n ENSURE(getLijnNr() == newLijnNr, "setLijnNr post condition failure");
  */
  void setLijnNr(const int newLijnNr);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setZitplaatsen");
  \n REQUIRE(newZitplaatsen >= 0 , "newZitplaatsen must be bigger or equal to zero");
  \n ENSURE(getZitplaatsen() == newZitplaatsen, "setZitplaatsen post condition failure");
  */
  void setZitplaatsen(const int newZitplaatsen);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setType");
  \n REQUIRE(newType != "", "newType must not be empty");
  \n ENSURE(getType() == newType, "setType post condition failure");
  */
  void setType(const std::string& newType);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setBeginStation");
  \n REQUIRE(newBeginStation != "", "newBeginStation must not be empty");
  \n ENSURE(getBeginStation() == newBeginStation, "setBeginStation post condition failure");
  */
  void setBeginStation(const std::string& newBeginStation);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  \n REQUIRE(newCurrentStation != "", "newCurrentStation must not be empty");
  \n ENSURE(getCurrentStation() == newCurrentStation, "setCurrentStation post condition failure");
  */
  void setCurrentStation(const std::string& newCurrentStation);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
  \n REQUIRE(newSnelheid >= 0 , "newSnelheid must be bigger or equal to zero");
  \n ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
  */
  void setSnelheid(const int newSnelheid);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setAantalPassagiers");
  \n REQUIRE(newAantalPassagiers >= 0 , "newAantalPassagiers must be bigger or equal to zero");
  \n ENSURE(getAantalPassagiers() == newAantalPassagiers, "setAantalPassagiers post condition failure");
  */
  void setAantalPassagiers(const int newAantalPassagiers);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setVoertuigNr");
  \n REQUIRE(newVoertuigNr >= 0 , "newVoertuigNr must be bigger or equal to zero");
  \n ENSURE(getVoertuigNr() == newVoertuigNr, "setVoertuigNr post condition failure");
  */
  void setVoertuigNr(const int newVoertuigNr);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setOmzet");
  \n REQUIRE(newOmzet >= 0 , "newOmzet must be bigger or equal to zero");
  \n ENSURE(getOmzet() == newOmzet, "setOmzet post condition failure");
  */
  void setOmzet(const int newOmzet);

	// MODIFIER METHODS
	/**
	\n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling isInTram");
	\n REQUIRE(passagier != "", "passagier must not be empty");
	*/
	bool isInTram(std::string passagier);
	/**
	\n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling addPassagier");
	\n REQUIRE(passagier != "", "passagier must not be empty");
	\n REQUIRE(isInTram(passagier) == false, "passenger allready in Tram");
	\n ENSURE(isInTram(passagier) == true, "addPassagier post condition failure");
	*/
	void addPassagier(std::string passagier, int aantal);
	/**
	\n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling removePassagier");
	\n REQUIRE(passagier != "", "passagier must not be empty");
	\n REQUIRE(isInTram(passagier) == true, "passenger not in Tram");
	\n ENSURE(isInTram(passagier) == false, "removePassagier post condition failure");
	*/
	void removePassagier(std::string passagier);
	/**
	\n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling afstappenInHalte");
	\n REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling afstappenInHalte");
	\n REQUIRE(station != "", "station must not be empty");
	*/
	std::set<std::string> afstappenInHalte(MetroNet& metronet, std::string station);
	/**
	\n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling afstappenInHalte");
	\n REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling afstappenInHalte");
	\n REQUIRE(station != "", "station must not be empty");
	*/
	bool stoptInStation(MetroNet& metronet, std::string station);

};


#endif /* INC_TRAM_H */
