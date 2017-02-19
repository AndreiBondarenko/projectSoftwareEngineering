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
  std::set<unsigned int> alleSporen; // is this data member needed?
public:
  // CONSTRUCTOR
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  MetroNet();

  // DESTRUCTOR
  ~MetroNet();

  // INITIALIZATION CHECK
  bool properlyInitialized() const;

  // GETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getAlleStations");
  */
  std::map<std::string, Station*>* getAlleStations();
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getAlleTrams");
  */
  std::map<int, Tram*>* getAlleTrams();
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getAlleSporen");
  */
  std::set<unsigned int>* getAlleSporen();

  // SETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling setAlleStations");
  \n ENSURE(*getAlleStations() == newAlleStations, "setAlleStations post condition failure");
  */
  void setAlleStations(std::map<std::string, Station*>& newAlleStations);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling setAlleTrams");
  \n ENSURE(*getAlleTrams() == newAlleTrams, "setAlleTrams post condition failure");
  */
  void setAlleTrams(std::map<int, Tram*>& newAlleTrams);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling setAlleSporen");
  \n ENSURE(*getAlleSporen() == newAlleSporen, "setAlleSporen post condition failure");
  */
  void setAlleSporen(std::set<unsigned int>& newAlleSporen);

  // MODIFIER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addStation");
  \n REQUIRE(getAlleStations()->count(newStation->getNaam()) == 0, "This MetroNet already contains a station with this name");
  \n ENSURE(getAlleStations()->at(newStation->getNaam()) == newStation, "addStation post condition failure");
  */
  void addStation(Station* newStation);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling removeStation");
  \n REQUIRE(getAlleStations()->count(newStation->getNaam()) == 1, "This MetroNet doesn't contain a station with this name");
  \n ENSURE(getAlleStations()->count(newStation->getNaam()) == 0, "removeStation post condition failure");
  */
  void removeStation(const std::string& stationName);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addTram");
  \n REQUIRE(getAlleTrams()->count(newTram->getLijnNr()) == 0, "This MetroNet already contains a Tram with this lijnNr");
  \n ENSURE(getAlleTrams()->at(newTram->getLijnNr()) == newTram, "addTram post condition failure");
  */
  void addTram(Tram* newTram);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling removeTram");
  \n REQUIRE(getAlleTrams()->count(newTram->getLijnNr()) == 1, "This MetroNet doesn't contain a tram with this lijnNr");
  \n ENSURE(getAlleTrams()->count(newTram->getLijnNr()) == 0, "removeTram post condition failure");
  */
  void removeTram(const unsigned int lijnNr);


protected:

};


#endif /* INC_METRONET_H */
