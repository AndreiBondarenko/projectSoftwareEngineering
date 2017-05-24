#ifndef INC_STATION_H
#define INC_STATION_H
#pragma once

#include <string>
#include <map>
#include <set>

class MetroNet;

class Station {
protected:
  friend class ClassTestStation;
  Station* initCheck;
  std::string naam;
  std::map<int, std::string> vorige;
  std::map<int, std::string> volgende;
  std::map<std::pair<int, int>, bool> tramInStation;
  std::set<std::string> passagiers;

  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(); // default
  /**
  \n REQUIRE(naam != "", "naam must not be empty");
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(const std::string& naam); // full

public:
  // DESTRUCTOR
  virtual ~Station();

  // INITIALIZATION CHECK
  bool properlyInitialized() const;

  // GETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getNaam");
  */
  std::string getNaam() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getVorige");
  \n REQUIRE(spoor >= 0, "parameter spoor must be >= 0, when passed to getVorige");
  */
  std::string getVorige(const int& spoor) const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getVolgende");
  \n REQUIRE(spoor >= 0, "parameter spoor must be >= 0, when passed to getVolgende");
  */
  std::string getVolgende(const int& spoor) const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getSporen");
  */
  std::set<int> getSporen() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling isTramInStation");
  \n REQUIRE(spoor >= 0, "parameter spoor must be >= 0, when passed to isTramInStation");
  */
  bool isTramInStation(const int& spoor) const;
	/**
	\n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getTramInStation");
	\n REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
	\n REQUIRE(isTramInStation(spoor), "no tram in station when calling getTramInStation");
	*/
	int getTramInStation(const int spoor) const;

  // SETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setNaam");
  \n REQUIRE(newNaam != "", "newNaam must not be empty");
  \n ENSURE(getNaam() == newNaam, "setNaam post condition failure");
  */
  void setNaam(const std::string& newNaam);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setVorige");
  \n REQUIRE(newVorige != "", "newVorige must not be empty");
  \n REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
  \n ENSURE(getVorige() == newVorige, "setVorige post condition failure");
  */
  void addVorige(const int& spoor, const std::string& newVorige);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setVolgende");
  \n REQUIRE(newVolgende != "", "newVolgende must not be empty");
  \n REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
  \n ENSURE(getVolgende() == newVolgende, "setVolgende post condition failure");
  */
  void addVolgende(const int& spoor, const std::string& newVolgende);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setTramInStation");
	\n REQUIRE(spoor >= 0, "spoor must be bigger or equal to zero");
	\n REQUIRE(voertuigNr >= 0, "voertuigNr must be bigger or equal to zero");
	\n ENSURE(isTramInStation(spoor) != newTramInStation, "setTramInStation post condition failure");  // false
  \n ENSURE(isTramInStation(spoor) == newTramInStation, "setTramInStation post condition failure");  // true
  */
  bool setTramInStation(const int& spoor, const int voertuigNr, const bool& newTramInStation);

	// MODIFIER METHODS
	/**
	\n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling isInStation");
	\n REQUIRE(passagier != "", "passagier must not be empty");
	*/
	bool isInStation(std::string passagier);
	/**
	\n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling addPassagier");
	\n REQUIRE(passagier != "", "passagier must not be empty");
	\n REQUIRE(isInStation(passagier) == false, "passenger allready in isInStation");
	\n ENSURE(isInStation(passagier) == true, "addPassagier post condition failure");
	*/
	void addPassagier(std::string passagier);
	/**
	\n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling removePassagier");
	\n REQUIRE(passagier != "", "passagier must not be empty");
	\n REQUIRE(isInStation(passagier) == true, "passenger not in isInStation");
	\n ENSURE(isInStation(passagier) == false, "removePassagier post condition failure");
	*/
	void removePassagier(std::string passagier);
	/**
	\n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling movePassagiers");
	\n REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling movePassagiers");
	\n ENSURE(metronet.isConsistent(), "movePassagiers made MetroNet inconsistent");
	*/
	void movePassagiers(MetroNet& metronet, std::ostream& output);

  // VIRTUAL METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling albatrosCanStop");
  */
  virtual bool albatrosCanStop() const;

private:
	/**
	\n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getTramInStation");
	*/
	std::set<int> getTramInStation() const;
};


#endif /* INC_STATION_H */
