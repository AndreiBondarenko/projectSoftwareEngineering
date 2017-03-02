#include <gtest/gtest.h>

#include "MetroNet.h"


class MetroNetClassTest: public ::testing::Test {
protected:
	friend class MetroNet;
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	Tram tram;
	Station station;
  MetroNet metronet;

};

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

}

TEST_F(MetroNetClassTest, SettersGettersMetroNet) {

}

TEST_F(MetroNetClassTest, ContractViolationsTram) {

}

TEST_F(MetroNetClassTest, ContractViolationsStation) {

}

TEST_F(MetroNetClassTest, ContractViolationsMetroNet) {

}
