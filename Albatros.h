#ifndef INC_ALBATROS_H
#define INC_ALBATROS_H
#pragma once

#include "Tram.h"

class Albatros: public Tram {
public:
  // CONSTRUCTORS
  /**
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Albatros(); // default
  /**
  \n REQUIRE(beginStation != "", "newBeginStation must not be empty");
  \n REQUIRE(lijnNr >= 0 , "lijnNr must be bigger or equal to zero");
  \n REQUIRE(newVoertuigNr >= 0 , "newVoertuigNr must be bigger or equal to zero");
  \n REQUIRE(zitplaatsen >= 0 , "zitplaatsen must be bigger or equal to zero");
  \n REQUIRE(snelheid >= 0 , "snelheid must be bigger or equal to zero");
  \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
  */
  Albatros(const int lijnNr, const int voertuigNr,
    const int zitplaatsen, const std::string& beginStation, const int snelheid); // full

  // DESTRUCTOR
  ~Albatros();

  /**
  \n REQUIRE(properlyInitialized(), "Albatros wasn't initialized when calling afstappenInHalte");
  \n REQUIRE(metronet.properlyInitialized(), "MetroNet wasn't initialized when calling afstappenInHalte");
  \n REQUIRE(station != "", "station must not be empty");
  */
  bool stoptInStation(MetroNet& metronet, std::string station) const;
};


#endif /* INC_ALBATROS_H */
