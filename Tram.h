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
  Tram* InitCheck;
  int LijnNr;
  int Zitplaatsen;
  std::string BeginStation;
  int Snelheid;
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(); // default
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Tram(int lijnNr, int zitplaatsen, std::string beginStation, int snelheid); // full

  // DESTRUCTOR
  ~Tram();

  // INITIALIZATION CHECK
  bool properlyInitialized();

  // GETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getLijnNr");
  */
  int getLijnNr() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getZitplaatsen");
  */
  int getZitplaatsen() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getBeginStation");
  */
  std::string getBeginStation() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
  */
  int getSnelheid() const;

  // SETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setLijnNr");
  \n ENSURE(this->getLijnNr() == newLijnNr, "setLijnNr post condition failure");
  */
  void setLijnNr(int newLijnNr);
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setZitplaatsen");
  \n ENSURE(this->getZitplaatsen() == newZitplaatsen, "setZitplaatsen post condition failure");
  */
  void setZitplaatsen(int newZitplaatsen);
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setBeginStation");
  \n ENSURE(this->getBeginStation() == newBeginStation, "setBeginStation post condition failure");
  */
  void setBeginStation(std::string newBeginStation);
  /**
  \n REQUIRE(this->properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
  \n ENSURE(this->getSnelheid() == newSnelheid, "setSnelheid post condition failure");
  */
  void setSnelheid(int newSnelheid);

protected:

};


#endif /* INC_TRAM_H */
