//
//  MetroNet.h
//  projectSoftwareEngineering
//
//  Created by Andrei Bondarenko on 17/02/2017.
//
//

#ifndef INC_METRONET_H
#define INC_METRONET_H

#include <map>
#include <set>
#include <string>
#include "Tram.h"
#include "Station.h"

class MetroNet {
private:
  MetroNet* initCheck;
  std::map<std::string, Station*> alleStations;
  std::map<int, Tram*> alleTrams;
  std::set<int> alleSporen;
public:
  // CONSTRUCTOR
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  MetroNet();

  // DESTRUCTOR
  ~MetroNet();

  // INITIALIZATION CHECK
  bool properlyInitialized();

  // GETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling getAlleStations");
  */
  std::map<std::string, Station*>* getAlleStations() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling getAlleTrams");
  */
  std::map<int, Station*>* getAlleTrams() const;
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling getAlleSporen");
  */
  std::set<int>* getAlleSporen() const;

  // SETTER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling setAlleStations");
  \n ENSURE(*(this->getAlleStations()) == newAlleStations, "setAlleStations post condition failure");
  */
  void setAlleStations(std::map<std::string, Station*> newAlleStations);
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling setAlleTrams");
  \n ENSURE(*(this->getAlleTrams()) == newAlleTrams, "setAlleTrams post condition failure");
  */
  void setAlleTrams(std::map<int, Station*> newAlleTrams);
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling setAlleSporen");
  \n ENSURE(*(this->getAlleSporen()) == newAlleSporen, "setAlleSporen post condition failure");
  */
  void setAlleSporen(std::set<int> newAlleSporen);

  // MODIFIER METHODS
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling addStation");
  \n REQUIRE((this->getAlleStations())->count(newStation->getNaam()) == 0, "This MetroNet already contains a station with this name");
  \n ENSURE((this->getAlleStations())->at(newStation->getNaam()) == newStation, "addStation post condition failure");
  */
  void addStation(Station* newStation);
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling removeStation");
  \n REQUIRE((this->getAlleStations())->count(newStation->getNaam()) == 1, "This MetroNet doesn't contain a station with this name");
  \n ENSURE((this->getAlleStations())->count(newStation->getNaam()) == 0, "removeStation post condition failure");
  */
  void removeStation(std::string stationName);
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling addTram");
  \n REQUIRE((this->getAlleTrams())->count(newTram->getLijnNr()) == 0, "This MetroNet already contains a Tram with this lijnNr");
  \n ENSURE((this->getAlleTrams())->at(newTram->getLijnNr()) == newTram, "addTram post condition failure");
  */
  void addTram(Tram* newTram);
  /**
  \n REQUIRE(this->properlyInitialized(), "MetroNet wasn't initialized when calling removeTram");
  \n REQUIRE((this->getAlleTrams())->count(newTram->getLijnNr()) == 1, "This MetroNet doesn't contain a tram with this lijnNr");
  \n ENSURE((this->getAlleTrams())->count(newTram->getLijnNr()) == 0, "removeTram post condition failure");
  */
  void removeTram(int lijnNr);


protected:

};


#endif /* INC_METRONET_H */
