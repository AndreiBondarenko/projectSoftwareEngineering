#ifndef INC_STATION_H
#define INC_STATION_H
#pragma once

#include <string>
#include <set>

class Station {
private:
  Station* initCheck;
  std::string naam;
  std::string vorige;
  std::string volgende;
  std::string type;
  int spoor;
  int opstappen;
  int afstappen;
  bool tramInStation;
	std::set<std::string> passagiers;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(); // default
  /**
  \n REQUIRE(volgende != "", "volgende must not be empty");
  \n REQUIRE(vorige != "", "vorige must not be empty");
  \n REQUIRE(naam != "", "naam must not be empty");
  \n REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(const std::string& naam, const std::string& vorige,
    const std::string& volgende, const int spoor); // full

  // DESTRUCTOR
  ~Station();

  // INITIALIZATION CHECK
  bool properlyInitialized() const;

  // GETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getNaam");
  */
  std::string getNaam() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getVorige");
  */
  std::string getVorige() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getVolgende");
  */
  std::string getVolgende() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getType");
  */
  std::string getType() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getSpoor");
  */
  int getSpoor() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getTramInStation");
  */
  bool isTramInStation() const;

  // OPTIONAL FEATURES
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getOpstappen");
  */
  int getOpstappen() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getAfstappen");
  */
  int getAfstappen() const;

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
  \n ENSURE(getVorige() == newVorige, "setVorige post condition failure");
  */
  void setVorige(const std::string& newVorige);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setVolgende");
  \n REQUIRE(newVolgende != "", "newVolgende must not be empty");
  \n ENSURE(getVolgende() == newVolgende, "setVolgende post condition failure");
  */
  void setVolgende(const std::string& newVolgende);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setType");
  \n REQUIRE(newType != "", "newType must not be empty");
  \n ENSURE(getType() == newType, "setType post condition failure");
  */
  void setType(const std::string& newType);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setSpoor");
  \n REQUIRE(newSpoor >= 0 , "newSpoor must be bigger or equal to zero");
  \n ENSURE(getSpoor() == newSpoor, "setSpoor post condition failure");
  */
  void setSpoor(const int newSpoor);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setTramInStation");
  \n ENSURE(isTramInStation() == newTramInStation, "setTramInStation post condition failure");
  */
  void setTramInStation(bool newTramInStation);

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

  // OPTIONAL FEATURES
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setOpstappen");
  \n REQUIRE(newOpstappen >= 0 , "newOpstappen must be bigger or equal to zero");
  \n ENSURE(getOpstappen() == newOpstappen, "setOpstappen post condition failure");
  */
  void setOpstappen(const int newOpstappen);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setAfstappen");
  \n REQUIRE(newAfstappen >= 0 , "newAfstappen must be bigger or equal to zero");
  \n ENSURE(getAfstappen() == newAfstappen, "setAfstappen post condition failure");
  */
  void setAfstappen(const int newAfstappen);


};


#endif /* INC_STATION_H */
