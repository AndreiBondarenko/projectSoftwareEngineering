#ifndef INC_PASSAGIER_H
#define INC_PASSAGIER_H

#include <string>

class Passagier {
private:
	Passagier* initCheck;
	std::string naam;
	std::string beginStation;
	std::string eindStation;
	int hoeveelheid;
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
	\n REQUIRE(newEindStation >= 0 , "newEindStation must not be empty");
	\n ENSURE(getEindStation() == newEindStation, "setEindStation post condition failure");
	*/
	void setEindStation(const std::string& newEindStation);
	/**
	\n REQUIRE(properlyInitialized(), "Passagier wasn't initialized when calling setHoeveelheid");
	\n REQUIRE(newHoeveelheid >= 0 , "newHoeveelheid must be bigger or equal to zero");
	\n ENSURE(getHoeveelheid() == newHoeveelheid, "setHoeveelheid post condition failure");
	*/
	void setHoeveelheid(const int newHoeveelheid);
};


#endif /* INC_PASSAGIER_H */
