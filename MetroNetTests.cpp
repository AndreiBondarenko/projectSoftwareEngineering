#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

#include "MetroNet.h"
#include "ClassTestsTram.cpp"
#include "ClassTestsStation.cpp"
#include "ClassTestsMetroNet.cpp"
#include "ClassTestsPassagier.cpp"


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
