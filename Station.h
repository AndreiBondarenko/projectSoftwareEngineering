//
//  Station.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef INC_STATION_H
#define INC_STATION_H

#include <string>

class Station {
private:
  Station* initCheck;
  std::string naam;
  std::string vorige;
  std::string volgende;
  int spoor;
  int opstappen;
  int afstappen;
  bool tramInStation;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(); // default
  /**
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
  \n ENSURE(getNaam() == newNaam, "setNaam post condition failure");
  */
  void setNaam(const std::string& newNaam);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setVorige");
  \n ENSURE(getVorige() == newVorige, "setVorige post condition failure");
  */
  void setVorige(const std::string& newVorige);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setVolgende");
  \n ENSURE(getVolgende() == newVolgende, "setVolgende post condition failure");
  */
  void setVolgende(const std::string& newVolgende);
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


protected:

};


#endif /* INC_STATION_H */
