#include <gtest/gtest.h>
#include "MetroNet.h"

class ClassTestStation: public ::testing::Test {
protected:
	friend class MetroNet;

  Station station;
	Halte halte;
	MetroStation metroStation;
  MetroNet metronet;

};

TEST_F(ClassTestStation, DefaultConstructors) {
  EXPECT_TRUE(station.properlyInitialized());
  EXPECT_TRUE(halte.properlyInitialized());
  EXPECT_TRUE(metroStation.properlyInitialized());
}

TEST_F(ClassTestStation, SettersGetters) {
  station.setNaam("Antwerpen");
  EXPECT_EQ("Antwerpen", station.getNaam());
  station.addVorige(13, "Vorige");
  EXPECT_EQ("Vorige", station.getVorige(13));
  station.addVolgende(13, "Volgende");
  EXPECT_EQ("Volgende", station.getVolgende(13));
  EXPECT_EQ(13, *station.getSporen().begin());
  station.setTramInStation(13, 33, true);
  EXPECT_TRUE(station.isTramInStation(13));
  EXPECT_EQ(33, station.getTramInStation(13));
  station.addPassagier("groep1");
  EXPECT_TRUE(station.isInStation("groep1"));
  station.removePassagier("groep1");
  EXPECT_FALSE(station.isInStation("groep1"));
  EXPECT_FALSE(halte.albatrosCanStop());
  EXPECT_TRUE(metroStation.albatrosCanStop());
}

TEST_F(ClassTestStation, ContractViolations) {
  EXPECT_DEATH(Halte(""), "naam must not be empty");
  EXPECT_DEATH(MetroStation(""), "naam must not be empty");
  EXPECT_DEATH(station.getVorige(-1), "parameter spoor must be >= 0, when passed to getVorige");
  EXPECT_DEATH(station.getVolgende(-1), "parameter spoor must be >= 0, when passed to getVolgende");
  EXPECT_DEATH(station.isTramInStation(-1), "parameter spoor must be >= 0, when passed to isTramInStation");
  EXPECT_DEATH(station.getTramInStation(-1), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.setNaam(""), "newNaam must not be empty");
  EXPECT_DEATH(station.addVorige(1 ,""), "newVorige must not be empty");
  EXPECT_DEATH(station.addVorige(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.addVolgende(1 ,""), "newVolgende must not be empty");
  EXPECT_DEATH(station.addVolgende(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.setTramInStation(-1, 1, true), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(station.setTramInStation(1, -1, true), "voertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(station.isInStation(""), "passagier must not be empty");
  EXPECT_DEATH(station.addPassagier(""), "passagier must not be empty");
  EXPECT_DEATH(station.removePassagier(""), "passagier must not be empty");
}
