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
  unsigned int spoor;
  unsigned int tramInStation;
// unsigned int opstappen;
// unsigned int afstappen;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(); // default
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(const std::string& naam, const std::string& vorige,
    const std::string& volgende, const unsigned int spoor); // full

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
  unsigned int getSpoor() const;
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getTramInStation");
  */
  unsigned int getTramInStation() const;

  // OPTIONAL FEATURES
  // /**
  // \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getOpstappen");
  // */
  // unsigned int getOpstappen() const;
  // /**
  // \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling getAfstappen");
  // */
  // unsigned int getAfstappen() const;

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
  \n ENSURE(getSpoor() == newSpoor, "setSpoor post condition failure");
  */
  void setSpoor(const unsigned int newSpoor);
  /**
  \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setTramInStation");
  \n ENSURE(getTramInStation() == newTramInStation, "setTramInStation post condition failure");
  */
  void setTramInStation(const unsigned int newTramInStation);

  // OPTIONAL FEATURES
  // /**
  // \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setOpstappen");
  // \n ENSURE(getOpstappen() == newOpstappen, "setOpstappen post condition failure");
  // */
  // void setOpstappen(const unsigned int newOpstappen);
  // /**
  // \n REQUIRE(properlyInitialized(), "Station wasn't initialized when calling setAfstappen");
  // \n ENSURE(getAfstappen() == newAfstappen, "setAfstappen post condition failure");
  // */
  // void setAfstappen(const unsigned int newAfstappen);


protected:

};


#endif /* INC_STATION_H */
