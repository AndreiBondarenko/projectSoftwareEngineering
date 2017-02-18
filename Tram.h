//
//  Tram.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef INC_TRAM_H
#define INC_TRAM_H

#include <string>

class Tram {
private:
  Tram* initCheck;
  unsigned int lijnNr;
  unsigned int zitplaatsen;
  std::string beginStation;
  unsigned int snelheid;
  static unsigned int aantalTrams;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(); // default
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(const unsigned int lijnNr, const unsigned int zitplaatsen, const std::string& beginStation,
	  const unsigned int snelheid); // full

  // DESTRUCTOR
  ~Tram();

  // INITIALIZATION CHECK
  bool properlyInitialized() const;

  // GETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLijnNr");
  */
  unsigned int getLijnNr() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getZitplaatsen");
  */
  unsigned int getZitplaatsen() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getBeginStation");
  */
  std::string getBeginStation() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
  */
  unsigned int getSnelheid() const;

  // SETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLijnNr");
  \n ENSURE(this->getLijnNr() == newLijnNr, "setLijnNr post condition failure");
  */
  void setLijnNr(const unsigned int newLijnNr);
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setZitplaatsen");
  \n ENSURE(this->getZitplaatsen() == newZitplaatsen, "setZitplaatsen post condition failure");
  */
  void setZitplaatsen(const unsigned int newZitplaatsen);
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setBeginStation");
  \n ENSURE(this->getBeginStation() == newBeginStation, "setBeginStation post condition failure");
  */
  void setBeginStation(const std::string& newBeginStation);
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
  \n ENSURE(this->getSnelheid() == newSnelheid, "setSnelheid post condition failure");
  */
  void setSnelheid(const unsigned int newSnelheid);

protected:

};


#endif /* INC_TRAM_H */
