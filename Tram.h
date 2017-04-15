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
  int lijnNr;
  int voertuigNr;
  int zitplaatsen;
  int passagiers;
  int snelheid;
  std::string type;
  std::string beginStation;
  std::string currentStation;
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
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getPassagiers");
  */
  int getPassagiers() const;
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling getVoertuigNr");
  */
  int getVoertuigNr() const;

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
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setPassagiers");
  \n REQUIRE(newPassagiers >= 0 , "newPassagiers must be bigger or equal to zero");
  \n ENSURE(getPassagiers() == newPassagiers, "setPassagiers post condition failure");
  */
  void setPassagiers(const int newPassagiers);
  /**
  \n REQUIRE(properlyInitialized(), "Tram wasn't initialized when calling setVoertuigNr");
  \n REQUIRE(newVoertuigNr >= 0 , "newVoertuigNr must be bigger or equal to zero");
  \n ENSURE(getVoertuigNr() == newVoertuigNr, "setVoertuigNr post condition failure");
  */
  void setVoertuigNr(const int newVoertuigNr);

};


#endif /* INC_TRAM_H */
