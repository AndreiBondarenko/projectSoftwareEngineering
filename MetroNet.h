#ifndef INC_METRONET_H
#define INC_METRONET_H
#pragma once

#include <map>
#include <set>
#include <string>
#include "Passagier.h"
#include "PCC.h"
#include "Albatros.h"
#include "Halte.h"
#include "MetroStation.h"


class Station;
class Tram;
class Passagier;

class MetroNet {
private:
  MetroNet* initCheck;
  std::map<std::string, Station*> alleStations;
  std::map<int, Tram*> alleTrams;
  std::set<int> alleSporen;
  std::map<std::string, Passagier*> allePassagiers;
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
  bool isConsistent();

  // GETTER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getAlleStations");
  \n REQUIRE(naam != "", "naam must not be empty");
  */
  Station* getStation(std::string naam);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getAlleTrams");
  \n REQUIRE(voertuigNr >= 0, "voertuigNr must be greater or equal to zero");
  */
  Tram* getTram(int voertuigNr);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling getPassagier");
  \n REQUIRE(naam != "", "naam must not be empty");
  */
  Passagier* getPassagier(std::string naam);

  // MODIFIER METHODS
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addStation");
  \n REQUIRE(getStation(newStation->getNaam()) == nullptr, "This MetroNet already contains a station with this name");
  \n ENSURE(getStation(newStation->getNaam()) == newStation, "addStation post condition failure");
  */
  void addStation(Station* newStation);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addTram");
  \n REQUIRE(getTram(newTram->voertuigNr()) == nullptr, "This MetroNet already contains a Tram with this voertuigNr");
	\n REQUIRE(getStation(newTram->getBeginStation())->isTramInStation(newTram->getLijnNr()) == false, "BeginStation of newTram isn't empty");
  \n ENSURE(getTram(newTram->voertuigNr()) == newTram, "addTram post condition failure");
  \n ENSURE(getStation(newTram->getBeginStation())->isTramInStation(), "addTram post condition failure");
  */
  void addTram(Tram* newTram);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling addPassagier");
	\n REQUIRE(getPassagier(newPassagier->getNaam()) == nullptr, "This MetroNet allready contains a passenger with this name");
	\n ENSURE(getPassagier(newPassagier->getNaam) == newPassagier, "addPassagier post condition failure");
  */
  void addPassagier(Passagier* newPassagier);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAlleTrams");
  \n ENSURE(isConsistent(), "moveAlleTrams made MetroNet inconsistent");
  */
  void moveAlleTrams(std::ostream& output);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling moveAllePassengers");
  */
  void moveAllePassengers(std::ostream& output);
  /**
  \n REQUIRE(properlyInitialized(), "MetroNet wasn't initialized when calling runSimulation");
  \n ENSURE(isConsistent(), "runSimulation made MetroNet inconsistent");
  */
  void runSimulation(std::ostream& output, const bool live=false);

  // FILE I/O METHODS
  /**
  \n REQUIRE(isConsistent(), "MetroNet is not consistent");
  */
  void writeToOutputStream(std::ostream& output);
  /**
  \n REQUIRE(isConsistent(), "MetroNet is not consistent");
  */
  void drawToOutputStream(std::ostream& output);

  void writeToASCII();

};


#endif /* INC_METRONET_H */
