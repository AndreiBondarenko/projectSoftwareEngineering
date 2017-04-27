#include <gtest/gtest.h>

#include "MetroNet.h"

//
// Voor volgende functies zijn geen of enkel death-tests geschreven:
// void moveToBeginStation(MetroNet& metronet) const;
//

class ClassTestPassagier: public ::testing::Test {
protected:
	friend class MetroNet;

  Passagier passagier;

};

TEST_F(ClassTestPassagier, DefaultConstructors) {
  EXPECT_TRUE(passagier.properlyInitialized());
  EXPECT_FALSE(passagier.isAangekomen());
}

TEST_F(ClassTestPassagier, SettersGetters) {
  passagier.setNaam("TEST");
  EXPECT_EQ("TEST", passagier.getNaam());
  passagier.setBeginStation("TEST");
  EXPECT_EQ("TEST", passagier.getBeginStation());
  passagier.setEindStation("TEST");
  EXPECT_EQ("TEST", passagier.getEindStation());
  passagier.setHoeveelheid(1);
  EXPECT_EQ(1, passagier.getHoeveelheid());
  passagier.markAangekomen();
  EXPECT_TRUE(passagier.isAangekomen());
}

TEST_F(ClassTestPassagier, ContractViolations) {
  EXPECT_DEATH(Passagier("", "testBegin", "testEinde", 1), "naam must not be empty");
  EXPECT_DEATH(Passagier("testNaam", "", "testEinde", 1), "beginStation must not be empty");
  EXPECT_DEATH(Passagier("testNaam", "testBegin", "", 1), "eindStation must not be empty");
  EXPECT_DEATH(Passagier("testNaam", "testBegin", "testEinde", -1), "hoeveelheid must be bigger or equal to zero");
  EXPECT_DEATH(passagier.setNaam(""), "newNaam must not be empty");
  EXPECT_DEATH(passagier.setBeginStation(""), "newBeginStation must not be empty");
  EXPECT_DEATH(passagier.setEindStation(""), "newEindStation must not be empty");
  EXPECT_DEATH(passagier.setHoeveelheid(-1), "newHoeveelheid must be bigger or equal to zero");
}
