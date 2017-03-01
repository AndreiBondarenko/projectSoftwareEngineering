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
  unsigned int passagiers;
  std::string beginStation;
  std::string currentStation;
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
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getCurrentStation");
  */
  std::string getCurrentStation() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getSnelheid");
  */
  unsigned int getSnelheid() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getPassagiers");
  */
  unsigned int getPassagiers() const;

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
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setCurrentStation");
  \n ENSURE(getCurrentStation() == newCurrentStation, "setCurrentStation post condition failure");
  */
  void setCurrentStation(const std::string& newCurrentStation);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setSnelheid");
  \n ENSURE(getSnelheid() == newSnelheid, "setSnelheid post condition failure");
  */
  void setSnelheid(const unsigned int newSnelheid);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setPassagiers");
  \n ENSURE(getPassagiers() == newPassagiers, "setPassagiers post condition failure");
  */
  void setPassagiers(const unsigned int newPassagiers);

  // // MODIFIER METHODS
  // /**
  // \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getOff");
  // \n REQUIRE(off <= getPassagiers(), "More passengers getting off Tram than on Tram");
  // \n ENSURE(getPassagiers() <= getZitplaatsen(), "getOff post condition failure");
  // */
  // void getOff(unsigned int off);
  // /**
  // \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getOn");
  // \n REQUIRE(on <= getZitplaatsen() - getPassagiers(), "Not enough seats for passengers getting on Tram");
  // \n ENSURE(getPassagiers() <= getZitplaatsen(), "getOn post condition failure");
  // */
  // void getOn(unsigned int on);

protected:

};


#endif /* INC_TRAM_H */
