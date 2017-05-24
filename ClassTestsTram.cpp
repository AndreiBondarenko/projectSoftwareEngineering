#include <gtest/gtest.h>

#include "MetroNet.h"


class ClassTestTram: public ::testing::Test {
protected:
	friend class MetroNet;

	PCC pcc;
  Albatros albatros;
  MetroNet net;

};

TEST_F(ClassTestTram, DefaultConstructors) {
  EXPECT_TRUE(albatros.properlyInitialized());
  EXPECT_TRUE(pcc.properlyInitialized());
}

TEST_F(ClassTestTram, SettersGetters) {
  albatros.setLijnNr(1);
  EXPECT_EQ(1, albatros.getLijnNr());
  albatros.setZitplaatsen(20);
  EXPECT_EQ(20, albatros.getZitplaatsen());
  albatros.setBeginStation("Antwerpen Centraal");
  EXPECT_EQ("Antwerpen Centraal", albatros.getBeginStation());
  albatros.setCurrentStation("Antwerpen niet Centraal");
  EXPECT_EQ("Antwerpen niet Centraal", albatros.getCurrentStation());
  albatros.setSnelheid(120);
  EXPECT_EQ(120, albatros.getSnelheid());
  albatros.setAantalPassagiers(2);
  EXPECT_EQ(2, albatros.getAantalPassagiers());
  albatros.setVoertuigNr(12);
  EXPECT_EQ(12, albatros.getVoertuigNr());
  albatros.setOmzet(50);
  EXPECT_EQ(50, albatros.getOmzet());
  albatros.addPassagier("Groep1", 2);
  EXPECT_TRUE(albatros.isInTram("Groep1"));
  albatros.removePassagier("Groep1");
  EXPECT_FALSE(albatros.isInTram("Groep1"));
  pcc.setLijnNr(1);
  EXPECT_EQ(1, pcc.getLijnNr());
  pcc.setZitplaatsen(20);
  EXPECT_EQ(20, pcc.getZitplaatsen());
  pcc.setBeginStation("Antwerpen Centraal");
  EXPECT_EQ("Antwerpen Centraal", pcc.getBeginStation());
  pcc.setCurrentStation("Antwerpen niet Centraal");
  EXPECT_EQ("Antwerpen niet Centraal", pcc.getCurrentStation());
  pcc.setSnelheid(120);
  EXPECT_EQ(120, pcc.getSnelheid());
  pcc.setAantalPassagiers(2);
  EXPECT_EQ(2, pcc.getAantalPassagiers());
  pcc.setVoertuigNr(12);
  EXPECT_EQ(12, pcc.getVoertuigNr());
  pcc.setOmzet(50);
  EXPECT_EQ(50, pcc.getOmzet());
  pcc.addPassagier("Groep1", 2);
  EXPECT_TRUE(pcc.isInTram("Groep1"));
  pcc.removePassagier("Groep1");
  EXPECT_FALSE(pcc.isInTram("Groep1"));
}

TEST_F(ClassTestTram, ContractViolations) {
  EXPECT_DEATH(Albatros(-1, 1, 1, "A", 1), "lijnNr must be bigger or equal to zero");
  EXPECT_DEATH(PCC(-1, 1, 1, "A", 1), "lijnNr must be bigger or equal to zero");
  EXPECT_DEATH(Albatros(1, -1, 1, "A", 1), "voertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(PCC(1, -1, 1, "A", 1), "voertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(Albatros(1, 1, -1, "A", 1), "zitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(PCC(1, 1, -1, "A", 1), "zitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(Albatros(1, 1, 1, "A", -1), "snelheid must be bigger or equal to zero");
  EXPECT_DEATH(PCC(1, 1, 1, "A", -1), "snelheid must be bigger or equal to zero");
  EXPECT_DEATH(Albatros(1, 1, 1, "", 1), "beginStation must not be empty");
  EXPECT_DEATH(PCC(1, 1, 1, "", 1), "beginStation must not be empty");
  EXPECT_DEATH(albatros.setCurrentStation(""), "newCurrentStation must not be empty");
  EXPECT_DEATH(pcc.setCurrentStation(""), "newCurrentStation must not be empty");
  EXPECT_DEATH(albatros.setBeginStation(""), "newBeginStation must not be empty");
  EXPECT_DEATH(pcc.setBeginStation(""), "newBeginStation must not be empty");
  EXPECT_DEATH(albatros.setLijnNr(-1), "newLijnNr must be bigger or equal to zero");
  EXPECT_DEATH(pcc.setLijnNr(-1), "newLijnNr must be bigger or equal to zero");
  EXPECT_DEATH(albatros.setZitplaatsen(-1), "newZitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(pcc.setZitplaatsen(-1), "newZitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(albatros.setSnelheid(-1), "newSnelheid must be bigger or equal to zero");
  EXPECT_DEATH(pcc.setSnelheid(-1), "newSnelheid must be bigger or equal to zero");
  EXPECT_DEATH(albatros.setAantalPassagiers(-1), "newAantalPassagiers must be bigger or equal to zero");
  EXPECT_DEATH(pcc.setAantalPassagiers(-1), "newAantalPassagiers must be bigger or equal to zero");
  EXPECT_DEATH(albatros.setVoertuigNr(-1), "newVoertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(pcc.setVoertuigNr(-1), "newVoertuigNr must be bigger or equal to zero");
  EXPECT_DEATH(albatros.addPassagier("Groep1", -1), "aantal must be bigger or equal to zero");
  EXPECT_DEATH(pcc.addPassagier("Groep1", -1), "aantal must be bigger or equal to zero");
  EXPECT_DEATH(albatros.addPassagier("", 1), "passagier must not be empty");
  EXPECT_DEATH(pcc.addPassagier("", 1), "passagier must not be empty");
  EXPECT_DEATH(albatros.removePassagier(""), "passagier must not be empty");
  EXPECT_DEATH(pcc.removePassagier(""), "passagier must not be empty");
  EXPECT_DEATH(albatros.afstappenInHalte(net, ""), "station must not be empty");
  EXPECT_DEATH(pcc.afstappenInHalte(net, ""), "station must not be empty");
}
