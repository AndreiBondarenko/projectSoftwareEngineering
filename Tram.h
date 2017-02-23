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
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getLijnNr");
  */
  unsigned int getLijnNr() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getZitplaatsen");
  */
  unsigned int getZitplaatsen() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getBeginStation");
  */
  std::string getBeginStation() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
  */
  unsigned int getSnelheid() const;

  // SETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setLijnNr");
  \n ENSURE(getLijnNr() == newLijnNr, "setLijnNr post condition failure");
  */
  void setLijnNr(const unsigned int newLijnNr);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setZitplaatsen");
  \n ENSURE(getZitplaatsen() == newZitplaatsen, "setZitplaatsen post condition failure");
  */
  void setZitplaatsen(const unsigned int newZitplaatsen);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setBeginStation");
  \n ENSURE(getBeginStation() == newBeginStation, "setBeginStation post condition failure");
  */
  void setBeginStation(const std::string& newBeginStation);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
  \n ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
  */
  void setSnelheid(const unsigned int newSnelheid);

protected:

};


#endif /* INC_TRAM_H */
