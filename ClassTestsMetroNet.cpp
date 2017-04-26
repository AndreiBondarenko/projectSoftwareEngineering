#include <gtest/gtest.h>

#include "MetroNet.h"


class ClassTestMetroNet: public ::testing::Test {
protected:
	friend class MetroNet;
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	Tram tram;
	Station station;
  MetroNet metronet;

};
/*
TEST_F(MetroNetClassTest, DefaultConstructors) {
  EXPECT_TRUE(tram.properlyInitialized());
  EXPECT_TRUE(station.properlyInitialized());
  EXPECT_TRUE(metronet.properlyInitialized());
}

TEST_F(MetroNetClassTest, SettersGettersTram) {
  tram.setLijnNr(1);
  EXPECT_EQ(1, tram.getLijnNr());
  tram.setZitplaatsen(20);
  EXPECT_EQ(20, tram.getZitplaatsen());
  tram.setBeginStation("Antwerpen Centraal");
  EXPECT_EQ("Antwerpen Centraal", tram.getBeginStation());
  tram.setCurrentStation("Antwerpen niet Centraal");
  EXPECT_EQ("Antwerpen niet Centraal", tram.getCurrentStation());
  tram.setSnelheid(120);
  EXPECT_EQ(120, tram.getSnelheid());
  tram.setPassagiers(2);
  EXPECT_EQ(2, tram.getPassagiers());
}

TEST_F(MetroNetClassTest, SettersGettersStation) {
  station.setNaam("Antwerpen");
  EXPECT_EQ("Antwerpen", station.getNaam());
  station.setVorige("Brussel");
  EXPECT_EQ("Brussel", station.getVorige());
  station.setVolgende("Amsterdam");
  EXPECT_EQ("Amsterdam", station.getVolgende());
  station.setSpoor(12);
  EXPECT_EQ(12, station.getSpoor());
  station.setTramInStation(true);
  EXPECT_TRUE(station.isTramInStation());
  station.setOpstappen(3);
  EXPECT_EQ(3, station.getOpstappen());
  station.setAfstappen(5);
  EXPECT_EQ(5, station.getAfstappen());
}

TEST_F(MetroNetClassTest, SettersGettersMetroNet) {
  Station* testStation1 = new Station("A", "Z", "B", 1);
  Station* testStation2 = new Station("B", "X", "Z", 1);
  metronet.addStation(testStation1);
	metronet.addStation(testStation2);
  EXPECT_EQ(stations, *(metronet.getAlleStations()));
  Tram* testTram = new Tram(1, 1, "B", 1);
  std::map<int, Tram*> trams;
  trams[testTram->getLijnNr()] = testTram;
  metronet.setAlleTrams(trams);
  EXPECT_EQ(trams, *(metronet.getAlleTrams()));
  std::set<int> sporen;
  sporen.insert(1); sporen.insert(8); sporen.insert(7);
  metronet.setAlleSporen(sporen);
  EXPECT_EQ(sporen, *(metronet.getAlleSporen()));
}

TEST_F(MetroNetClassTest, ContractViolationsTram) {
  EXPECT_DEATH(Tram(-1, 1, "A", 1), "lijnNr must be bigger or equal to zero");
  EXPECT_DEATH(Tram(1, -1, "A", 1), "zitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(Tram(1, 1, "A", -1), "snelheid must be bigger or equal to zero");
  EXPECT_DEATH(Tram(1, 1, "", 1), "beginStation must not be empty");
  EXPECT_DEATH(tram.setCurrentStation(""), "newCurrentStation must not be empty");
  EXPECT_DEATH(tram.setBeginStation(""), "newBeginStation must not be empty");
  EXPECT_DEATH(tram.setLijnNr(-1), "newLijnNr must be bigger or equal to zero");
  EXPECT_DEATH(tram.setZitplaatsen(-1), "newZitplaatsen must be bigger or equal to zero");
  EXPECT_DEATH(tram.setSnelheid(-1), "newSnelheid must be bigger or equal to zero");
  EXPECT_DEATH(tram.setPassagiers(-1), "newPassagiers must be bigger or equal to zero");
}

TEST_F(MetroNetClassTest, ContractViolationsStation) {
  EXPECT_DEATH(Station("A", "Z", "B", -1), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(Station("", "Z", "B", 1), "naam must not be empty");
  EXPECT_DEATH(Station("A", "", "B", 1), "vorige must not be empty");
  EXPECT_DEATH(Station("A", "Z", "", 1), "volgende must not be empty");
  EXPECT_DEATH(station.setNaam(""), "newNaam must not be empty");
  EXPECT_DEATH(station.setVolgende(""), "newVolgende must not be empty");
  EXPECT_DEATH(station.setVorige(""), "newVorige must not be empty");
  EXPECT_DEATH(station.setSpoor(-1), "newSpoor must be bigger or equal to zero");
  EXPECT_DEATH(station.setOpstappen(-1), "newOpstappen must be bigger or equal to zero");
  EXPECT_DEATH(station.setAfstappen(-1), "newAfstappen must be bigger or equal to zero");
}

TEST_F(MetroNetClassTest, ContractViolationsMetroNet) {
  Station* testStation1 = new Station("A", "Z", "B", 1);
  Station* testStation2 = new Station("B", "X", "Z", 1);
  metronet.addStation(testStation1);
  metronet.addStation(testStation2);
  EXPECT_DEATH(metronet.addStation(testStation1), "This MetroNet already contains a station with this name");
  Tram* testTram = new Tram(1, 1, "B", 1);
  metronet.addTram(testTram);
  EXPECT_DEATH(metronet.addTram(testTram), "This MetroNet already contains a Tram with this lijnNr");
  EXPECT_DEATH(metronet.moveTram("A", -1, std::cout), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(metronet.moveTram("", 1, std::cout), "station must not be empty");
  EXPECT_DEATH(metronet.movePassengers("A", -1, std::cout, std::cout), "spoor must be bigger or equal to zero");
  EXPECT_DEATH(metronet.movePassengers("", 1, std::cout, std::cout), "station must not be empty");
  EXPECT_DEATH(metronet.movePassengers("A", 1, std::cout, std::cout), "Tram not in given station");
  testStation2->setTramInStation(false);
  EXPECT_DEATH(metronet.movePassengers("B", 1, std::cout, std::cout), "Station is empty");
}
*/
