#include <gtest/gtest.h>
#include "MetroNet.h"

class ClassTestStation: public ::testing::Test {
protected:
	friend class MetroNet;

	Halte halte;
	MetroStation metroStation;
  	MetroNet metronet;

};

TEST_F(ClassTestStation, DefaultConstructors) {
  EXPECT_TRUE(halte.properlyInitialized());
  EXPECT_TRUE(metroStation.properlyInitialized());
}

TEST_F(ClassTestStation, SettersGetters) {
  halte.setNaam("Antwerpen");
  EXPECT_EQ("Antwerpen", halte.getNaam());
  halte.addVorige(13, "Vorige");
  EXPECT_EQ("Vorige", halte.getVorige(13));
  halte.addVolgende(13, "Volgende");
  EXPECT_EQ("Volgende", halte.getVolgende(13));
  EXPECT_EQ(13, *halte.getSporen().begin());
  halte.setTramInStation(13, 33, true);
  EXPECT_TRUE(halte.isTramInStation(13));
  EXPECT_EQ(33, halte.getTramInStation(13));
  halte.addPassagier("groep1");
  EXPECT_TRUE(halte.isInStation("groep1"));
  halte.removePassagier("groep1");
  EXPECT_FALSE(halte.isInStation("groep1"));
  EXPECT_FALSE(halte.albatrosCanStop());
  metroStation.setNaam("Antwerpen");
  EXPECT_EQ("Antwerpen", metroStation.getNaam());
  metroStation.addVorige(13, "Vorige");
  EXPECT_EQ("Vorige", metroStation.getVorige(13));
  metroStation.addVolgende(13, "Volgende");
  EXPECT_EQ("Volgende", metroStation.getVolgende(13));
  EXPECT_EQ(13, *metroStation.getSporen().begin());
  metroStation.setTramInStation(13, 33, true);
  EXPECT_TRUE(metroStation.isTramInStation(13));
  EXPECT_EQ(33, metroStation.getTramInStation(13));
  metroStation.addPassagier("groep1");
  EXPECT_TRUE(metroStation.isInStation("groep1"));
  metroStation.removePassagier("groep1");
  EXPECT_FALSE(metroStation.isInStation("groep1"));
  EXPECT_TRUE(metroStation.albatrosCanStop());
}

TEST_F(ClassTestStation, ContractViolations) {
  EXPECT_DEATH(MetroStation(""), "naam must not be empty");
  EXPECT_DEATH(Halte(""), "naam must not be empty");
  EXPECT_DEATH(metroStation.getVorige(-1), "parameter spoor must be >= 0, when passed to getVorige");
  EXPECT_DEATH(halte.getVorige(-1), "parameter spoor must be >= 0, when passed to getVorige");
  EXPECT_DEATH(metroStation.getVolgende(-1), "parameter spoor must be >= 0, when passed to getVolgende");
  EXPECT_DEATH(halte.getVolgende(-1), "parameter spoor must be >= 0, when passed to getVolgende");
  EXPECT_DEATH(metroStation.isTramInStation(-1), "parameter spoor must be >= 0, when passed to isTramInStation");
  EXPECT_DEATH(halte.isTramInStation(-1), "parameter spoor must be >= 0, when passed to isTramInStation");
  EXPECT_DEATH(metroStation.getTramInStation(-1), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(halte.getTramInStation(-1), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(metroStation.setNaam(""), "newNaam must not be empty");
  EXPECT_DEATH(halte.setNaam(""), "newNaam must not be empty");
  EXPECT_DEATH(metroStation.addVorige(1 ,""), "newVorige must not be empty");
  EXPECT_DEATH(halte.addVorige(1 ,""), "newVorige must not be empty");
  EXPECT_DEATH(metroStation.addVorige(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(halte.addVorige(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(metroStation.addVolgende(1 ,""), "newVolgende must not be empty");
  EXPECT_DEATH(halte.addVolgende(1 ,""), "newVolgende must not be empty");
  EXPECT_DEATH(metroStation.addVolgende(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(halte.addVolgende(-1 ,"TEST"), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(metroStation.setTramInStation(-1, 1, true), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(halte.setTramInStation(-1, 1, true), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(metroStation.setTramInStation(1, -1, true), "voertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(halte.setTramInStation(1, -1, true), "voertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(metroStation.isInStation(""), "passagier must not be empty");
  EXPECT_DEATH(halte.isInStation(""), "passagier must not be empty");
  EXPECT_DEATH(metroStation.addPassagier(""), "passagier must not be empty");
  EXPECT_DEATH(halte.addPassagier(""), "passagier must not be empty");
  EXPECT_DEATH(metroStation.removePassagier(""), "passagier must not be empty");
  EXPECT_DEATH(halte.removePassagier(""), "passagier must not be empty");
}
