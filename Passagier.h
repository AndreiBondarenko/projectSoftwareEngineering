#ifndef INC_PASSAGIER_H
#define INC_PASSAGIER_H
#pragma once

#include <string>
#include "MetroNet.h"

class MetroNet;

class Passagier {
private:
	Passagier* initCheck;
	std::string naam;
	std::string beginStation;
	std::string eindStation;
	int hoeveelheid;
    bool aangekomen = false;
public:
	// CONSTRUCTORS
	/**
	\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
	*/
	Passagier(); // default
	/**
	\n REQUIRE(naam != "", "naam must not be empty");
	\n REQUIRE(beginStation != "", "beginStation must not be empty");
	\n REQUIRE(eindStation != "", "eindStation must not be empty");
	\n REQUIRE(hoeveelheid >= 0 , "hoeveelheid must be bigger or equal to zero");
	\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
	*/
	Passagier(std::string naam, std::string beginStation, std::string eindStation, int hoeveelheid); // full

	// DESTRUCTOR
	~Passagier();

	// INITIALIZATION CHECK
	bool properlyInitialized() const;

	// GETTER METHODS
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getNaam");
	*/
	std::string getNaam() const;
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getBeginStation");
	*/
	std::string getBeginStation() const;
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getEindStation");
	*/
	std::string getEindStation() const;
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling getHoeveelheid");
	*/
	int getHoeveelheid() const;
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling isAangekomen");
	*/
	bool isAangekomen() const;


	// SETTER METHODS
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setNaam");
	\n REQUIRE(newNaam != "" , "newNaam must not be empty");
	\n ENSURE(getNaam() == newNaam, "setNaam post condition failure");
	*/
	void setNaam(const std::string& newNaam);
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setBeginStation");
	\n REQUIRE(newBeginStation != "" , "newBeginStation must not be empty");
	\n ENSURE(getBeginStation() == newBeginStation, "setBeginStation post condition failure");
	*/
	void setBeginStation(const std::string& newBeginStation);
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setEindStation");
	\n REQUIRE(newEindStation != "" , "newEindStation must not be empty");
	\n ENSURE(getEindStation() == newEindStation, "setEindStation post condition failure");
	*/
	void setEindStation(const std::string& newEindStation);
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setHoeveelheid");
	\n REQUIRE(newHoeveelheid >= 0 , "newHoeveelheid must be bigger or equal to zero");
	\n ENSURE(getHoeveelheid() == newHoeveelheid, "setHoeveelheid post condition failure");
	*/
	void setHoeveelheid(const int newHoeveelheid);

	// MODIFIER METHODS
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling moveToBeginStation");
	\n REQUIRE(metronet->properlyInitialized(), "MetroNet wasn't initialized when calling Passagier::moveToBeginStation");
	\n ENSURE(station->isInStation(naam), "moveToBeginStation post condition failure");
	\n ENSURE(metronet->isConsistent(), "Passagier::moveToBeginStation made MetroNet inconsistent");
	*/
	void moveToBeginStation(MetroNet& metronet) const;
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling markAangekomen");
	\n ENSURE(isAangekomen() == true, "markAangekomen post condition failure");
	*/
	void markAangekomen();
};


#endif /* INC_PASSAGIER_H */
