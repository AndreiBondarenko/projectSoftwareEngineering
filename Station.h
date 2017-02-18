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
// unsigned int opstappen;
// unsigned int afstappen;
  static unsigned int aantalStations;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(); // default
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Station(const std::string& naam, const std::string& vorige, const std::string& volgende, unsigned int spoor); // full

  // DESTRUCTOR
  ~Station();

  // INITIALIZATION CHECK
  bool properlyInitialized();

  // GETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getNaam");
  */
  std::string getNaam() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getVorige");
  */
  std::string getVorige() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getVolgende");
  */
  std::string getVolgende() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getSpoor");
  */
  unsigned int getSpoor() const;

  // OPTIONAL FEATURES
  // /**
  // \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getOpstappen");
  // */
  // unsigned int getOpstappen() const;
  // /**
  // \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling getAfstappen");
  // */
  // unsigned int getAfstappen() const;

  // SETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setNaam");
  \n ENSURE(this->getNaam() == newNaam, "setNaam post condition failure");
  */
  void setNaam(const std::string& newNaam);
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setVorige");
  \n ENSURE(this->getVorige() == newVorige, "setVorige post condition failure");
  */
  void setVorige(const std::string& newVorige);
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setVolgende");
  \n ENSURE(this->getVolgende() == newVolgende, "setVolgende post condition failure");
  */
  void setVolgende(const std::string& newVolgende);
  /**
  \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setSpoor");
  \n ENSURE(this->getSpoor() == newSpoor, "setSpoor post condition failure");
  */
  void setSpoor(const unsigned int newSpoor);

  // OPTIONAL FEATURES
  // /**
  // \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setOpstappen");
  // \n ENSURE(this->getOpstappen() == newOpstappen, "setOpstappen post condition failure");
  // */
  // void setOpstappen(const unsigned int newOpstappen);
  // /**
  // \n REQUIRE(this->properlyInitialized(), "Station wasn't initialized when calling setAfstappen");
  // \n ENSURE(this->getAfstappen() == newAfstappen, "setAfstappen post condition failure");
  // */
  // void setAfstappen(const unsigned int newAfstappen);


protected:

};


#endif /* INC_STATION_H */
