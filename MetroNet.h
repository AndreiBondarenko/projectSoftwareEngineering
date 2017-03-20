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
  std::set<int> alleSporen; // is this data member needed?
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

  // CONSISTENCY CHECK
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling isConsistent");
  */
  bool isConsistent() const;

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
  std::set<int>* getAlleSporen();

  // SETTER METHODS (MAINLY USED FOR TESTING PURPOSES)
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
  void setAlleSporen(std::set<int>& newAlleSporen);

  // MODIFIER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addStation");
  \n REQUIRE(getAlleStations()->count(newStation->getNaam()) == 0, "This MetroNet already contains a station with this name");
  \n ENSURE(getAlleStations()->at(newStation->getNaam()) == newStation, "addStation post condition failure");
  */
  void addStation(Station* newStation);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addTram");
  \n REQUIRE(getAlleTrams()->count(newTram->getLijnNr()) == 0, "This MetroNet already contains a Tram with this lijnNr");
  \n ENSURE(getAlleTrams()->at(newTram->getLijnNr()) == newTram, "addTram post condition failure");
  \n ENSURE(getAlleStations()->at(newTram->getBeginStation())->isTramInStation(), "addTram post condition failure");
  */
  void addTram(Tram* newTram);

  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveTram");
  \n REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  \n REQUIRE(station != "", "station must not be empty");
  \n ENSURE(getAlleStations()->at(station)->getTramInStation() != spoor, "moveTram post condition failure");
  \n ENSURE(station == getTrams()->at(spoor)->getCurrentStation(), "moveTram post condition failure");
  \n ENSURE(isConsistent(), "moveTram made MetroNet inconsistent");
  */
  void moveTram(std::string station, int spoor, std::ostream& output);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveTram");
  \n ENSURE(isConsistent(), "moveAlleTrams made MetroNet inconsistent");
  */
  void moveAlleTrams(std::ostream& output);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling movePassengers");
  \n REQUIRE(spoor >= 0 , "spoor must be bigger or equal to zero");
  \n REQUIRE(station != "", "station must not be empty");
  \n REQUIRE(getAlleTrams()->at(spoor)->getCurrentStation() == station, "Tram not in given station");
  \n REQUIRE(getAlleStations()->at(station)->isTramInStation(), "Station is empty");
  */
  void movePassengers(std::string station, int spoor, std::ostream& output, std::ostream& errors);

  // FILE I/O METHODS
  /**
  \n REQUIRE(isConsistent(), "MetroNet is not consistent");
  */
  void writeToOutputStream(std::ostream& output);

  void writeToASCII();



protected:

};


#endif /* INC_METRONET_H */
