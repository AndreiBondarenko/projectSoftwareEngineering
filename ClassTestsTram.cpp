#include <gtest/gtest.h>

#include "MetroNet.h"

//
// Voor volgende functies zijn geen of enkel death-tests geschreven:
// bool stoptInStation(MetroNet& metronet, std::string station) const;
// std::set<std::string> afstappenInHalte(MetroNet& metronet, std::string station);
// void moveTram(MetroNet& metronet, std::ostream& output);
//


class ClassTestTram: public ::testing::Test {
protected:
	friend class MetroNet;

	Tram tram;
  MetroNet net;

};

TEST_F(ClassTestTram, DefaultConstructor) {
  EXPECT_TRUE(tram.properlyInitialized());
}

TEST_F(ClassTestTram, SettersGetters) {
  tram.setLijnNr(1);
  EXPECT_EQ(1, tram.getLijnNr());
  tram.setZitplaatsen(20);
  EXPECT_EQ(20, tram.getZitplaatsen());
  tram.setType("Test");
  EXPECT_EQ("Test", tram.getType());
  tram.setBeginStation("Antwerpen Centraal");
  EXPECT_EQ("Antwerpen Centraal", tram.getBeginStation());
  tram.setCurrentStation("Antwerpen niet Centraal");
  EXPECT_EQ("Antwerpen niet Centraal", tram.getCurrentStation());
  tram.setSnelheid(120);
  EXPECT_EQ(120, tram.getSnelheid());
  tram.setAantalPassagiers(2);
  EXPECT_EQ(2, tram.getAantalPassagiers());
  tram.setVoertuigNr(12);
  EXPECT_EQ(12, tram.getVoertuigNr());
  tram.setOmzet(50);
  EXPECT_EQ(50, tram.getOmzet());
  tram.addPassagier("Groep1", 2);
  EXPECT_TRUE(tram.isInTram("Groep1"));
  tram.removePassagier("Groep1");
  EXPECT_FALSE(tram.isInTram("Groep1"));
}

TEST_F(ClassTestTram, ContractViolations) {
  EXPECT_DEATH(Tram(-1, 1, "test", 1, "A", 1), "lijnNr must be bigger or equal to zero");
  EXPECT_DEATH(Tram(1, -1, "test", 1, "A", 1), "voertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(Tram(1, 1, "test", -1, "A", 1), "zitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(Tram(1, 1, "test", 1, "A", -1), "snelheid must be bigger or equal to zero");
  EXPECT_DEATH(Tram(1, 1, "test", 1, "", 1), "beginStation must not be empty");
  EXPECT_DEATH(Tram(1, 1, "", 1, "A", 1), "type must not be empty");
  EXPECT_DEATH(tram.setCurrentStation(""), "newCurrentStation must not be empty");
  EXPECT_DEATH(tram.setBeginStation(""), "newBeginStation must not be empty");
  EXPECT_DEATH(tram.setLijnNr(-1), "newLijnNr must be bigger or equal to zero");
  EXPECT_DEATH(tram.setZitplaatsen(-1), "newZitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(tram.setSnelheid(-1), "newSnelheid must be bigger or equal to zero");
  EXPECT_DEATH(tram.setAantalPassagiers(-1), "newAantalPassagiers must be bigger or equal to zero");
  EXPECT_DEATH(tram.setType("Test"), "newType must not be empty");
  EXPECT_DEATH(tram.setVoertuigNr(-1), "newVoertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(tram.addPassagier("Groep1", -1), "aantal must be bigger or equal to zero");
  EXPECT_DEATH(tram.addPassagier("", 1), "passagier must not be empty");
  EXPECT_DEATH(tram.removePassagier(""), "passagier must not be empty");
  EXPECT_DEATH(tram.afstappenInHalte(net, ""), "station must not be empty");
}
