#include <gtest/gtest.h>

#include "MetroNet.h"

class ClassTestMetroNet: public ::testing::Test {
protected:
	friend class MetroNet;
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

  MetroNet metronet;

};

TEST_F(ClassTestMetroNet, DefaultConstructors) {
  EXPECT_TRUE(metronet.properlyInitialized());
}

TEST_F(ClassTestMetroNet, SettersGetters) {
  Station* testStation = new Halte("testNaam");
  metronet.addStation(testStation);
  EXPECT_EQ(testStation, metronet.getStation("testNaam"));
  Tram* testTram = new PCC(1, 1, 1, "testNaam", 1);
  metronet.addTram(testTram);
  EXPECT_EQ(testTram, metronet.getTram(1));
  Passagier* testPassagier = new Passagier("testNaam", "testBeginStation", "testEindStation", 1);
  metronet.addPassagier(testPassagier);
  EXPECT_EQ(testPassagier, metronet.getPassagier("testNaam"));
}

TEST_F(ClassTestMetroNet, ContractViolations) {
  EXPECT_DEATH(metronet.getStation(""), "naam must not be empty");
  EXPECT_DEATH(metronet.getTram(-1), "voertuigNr must be greater or equal to zero");
  EXPECT_DEATH(metronet.getPassagier(""), "naam must not be empty");
  Station* testStation = new Halte("testNaam");
  metronet.addStation(testStation);
  EXPECT_DEATH(metronet.addStation(testStation), "This MetroNet already contains a station with this name");
  Tram* testTram = new PCC(1, 1, 1, "testNaam", 1);
  metronet.addTram(testTram);
  EXPECT_DEATH(metronet.addTram(testTram), "This MetroNet already contains a Tram with this voertuigNr");
  Passagier* testPassagier = new Passagier("testNaam", "testBeginStation", "testEindStation", 1);
  metronet.addPassagier(testPassagier);
  EXPECT_DEATH(metronet.addPassagier(testPassagier), "This MetroNet allready contains a passenger with this name");
}
