#include <gtest/gtest.h>

#include "MetroNet.h"

//
// Voor volgende functies zijn geen of enkel death-tests geschreven:
// void movePassagiers(MetroNet& metronet, std::ostream& output, std::ostream& error);
//


class ClassTestStation: public ::testing::Test {
protected:
	friend class MetroNet;

	Station station;
  MetroNet metronet;

};

TEST_F(ClassTestStation, DefaultConstructor) {
  EXPECT_TRUE(station.properlyInitialized());
}

TEST_F(ClassTestStation, SettersGetters) {
  station.setNaam("Antwerpen");
  EXPECT_EQ("Antwerpen", station.getNaam());
  station.addVorige(13, "Vorige");
  EXPECT_EQ("Vorige", station.getVorige(13));
  station.addVolgende(13, "Volgende");
  EXPECT_EQ("Volgende", station.getVolgende(13));
  // EXPECT_EQ({13}, station.getSporen());  Google test framework kan geen set vergelijken, andere oplossing?
  station.setType("TEST");
  EXPECT_EQ("TEST", station.getType());
  station.setTramInStation(13, 33, true);
  EXPECT_TRUE(station.isTramInStation(13));
  EXPECT_EQ(33, station.getTramInStation(13));
  // EXPECT_EQ({33}, station.getTramInStation()); Google test framework kan geen set vergelijken, andere oplossing?
  station.addPassagier("groep1");
  EXPECT_TRUE(station.isInStation("groep1"));
  station.removePassagier("groep1");
  EXPECT_FALSE(station.isInStation("groep1"));
}

TEST_F(ClassTestStation, ContractViolationsStation) {
  EXPECT_DEATH(Station("", "TEST"), "naam must not be empty");
  EXPECT_DEATH(Station("TEST", ""), "type must not be empty");
  EXPECT_DEATH(station.getVorige(-1), "parameter spoor must be >= 0, when passed to getVorige");
  EXPECT_DEATH(station.getVolgende(-1), "parameter spoor must be >= 0, when passed to getVolgende");
  EXPECT_DEATH(station.isTramInStation(-1), "parameter spoor must be >= 0, when passed to isTramInStation");
  EXPECT_DEATH(station.getTramInStation(-1), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.setNaam(""), "newNaam must not be empty");
  EXPECT_DEATH(station.addVorige(1 ,""), "newVorige must not be empty");
  EXPECT_DEATH(station.addVorige(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.addVolgende(1 ,""), "newVolgende must not be empty");
  EXPECT_DEATH(station.addVolgende(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.setType(""), "newType must not be empty");
  EXPECT_DEATH(station.setTramInStation(-1, 1, true), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.setTramInStation(1, -1, true), "voertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(station.isInStation(""), "passagier must not be empty");
  EXPECT_DEATH(station.addPassagier(""), "passagier must not be empty");
  EXPECT_DEATH(station.removePassagier(""), "passagier must not be empty");
}
