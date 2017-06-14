#include <gtest/gtest.h>

#include "MetroNet.h"
#include "MetroNetImporter.h"
#include "MetroNetUtils.h"


class MetroNetOutputTest: public ::testing::Test {
protected:
	friend class MetroNet;
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	virtual void SetUp() {
		metronet = new MetroNet();
	}

	MetroNet* metronet = new MetroNet();

};

TEST_F(MetroNetOutputTest, FileCompareTest) {
	ASSERT_TRUE(DirectoryExists("_testOutput"));

	std::ofstream myfile;
	myfile.open("_testOutput/file1.txt");
	myfile.close();
	myfile.open("_testOutput/file2.txt");
	myfile.close();

	EXPECT_TRUE(FileExists("_testOutput/file1.txt"));
	EXPECT_TRUE(FileExists("_testOutput/file2.txt"));
	EXPECT_TRUE(FileIsEmpty("_testOutput/file1.txt"));
	EXPECT_TRUE(FileIsEmpty("_testOutput/file2.txt"));


	//compare 2 empty files
	EXPECT_TRUE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare an empty and a non-empty files
	myfile.open("_testOutput/file1.txt");
	myfile << "xxx" << std::endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileExists("_testOutput/file1.txt"));
	EXPECT_FALSE(FileIsEmpty("_testOutput/file1.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare two equal files
	myfile.open("_testOutput/file2.txt");
	myfile << "xxx" << std::endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileExists("_testOutput/file2.txt"));
	EXPECT_FALSE(FileIsEmpty("_testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare 2 non-empty files which are off by a character in the middle
	myfile.open("_testOutput/file2.txt");
	myfile << "xxx" << std::endl << "xyy";
	myfile.close();
	EXPECT_FALSE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare 2 non-empty files where one is one character shorter than the other
	myfile.open("_testOutput/file2.txt");
	myfile << "xxx" << std::endl << "yy";
	myfile.close();
	EXPECT_FALSE(FileCompare("_testOutput/file1.txt", "_testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("_testOutput/file2.txt", "_testOutput/file1.txt"));

	//compare existing against non existing file
	EXPECT_FALSE(
			FileCompare("_testOutput/file1.txt", "_testOutput/nonexisting.txt"));
	EXPECT_FALSE(
			FileCompare("_testOutput/nonexisting.txt", "_testOutput/file1.txt"));
}

TEST_F(MetroNetOutputTest, Simulation1TramPerLijnNoErrors) {

	std::ofstream errors;
    std::ofstream initOverview;
    std::ofstream initMap;
    std::ofstream postOverview;
    std::ofstream postMap;
    std::ofstream movement;
    int fileCounter = 1;
    std::string fileName1 = "_testInput/SimulationOutputTests/simulation1TramMetronet" + std::to_string(fileCounter) + ".xml";
    std::string fileName2 = "_testInput/SimulationOutputTests/simulation1TramPassagiers" + std::to_string(fileCounter) + ".xml";

    while (FileExists(fileName1) && FileExists(fileName2)) {
		SetUp();
		errors.open("_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "ErrorLog.txt");
		initOverview.open("_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "InitOverview.txt");
		initMap.open("_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "InitMap.txt");
		postOverview.open("_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "PostOverview.txt");
		postMap.open("_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "PostMap.txt");
		movement.open("_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "MovementLog.txt");
        MetroNetImporter::importMetroNet(fileName1.c_str(), errors, *metronet);
		MetroNetImporter::importPassengers(fileName2.c_str(), errors, *metronet);
		metronet->writeToOutputStream(initOverview);
		metronet->drawToOutputStream(initMap);
		metronet->runSimulation(movement);
		metronet->writeToOutputStream(postOverview);
		metronet->drawToOutputStream(postMap);
        errors.close();
        initOverview.close();
        initMap.close();
        postOverview.close();
        postMap.close();
        movement.close();

		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation1TramMetronet" + std::to_string(fileCounter) + "ErrorLogExpected.txt",
			"_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "ErrorLog.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation1TramMetronet" + std::to_string(fileCounter) + "InitOverviewExpected.txt",
			"_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "InitOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation1TramMetronet" + std::to_string(fileCounter) + "InitMapExpected.txt",
			"_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "InitMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation1TramMetronet" + std::to_string(fileCounter) + "PostOverviewExpected.txt",
			"_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "PostOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation1TramMetronet" + std::to_string(fileCounter) + "PostMapExpected.txt",
			"_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "PostMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation1TramMetronet" + std::to_string(fileCounter) + "MovementLogExpected.txt",
			"_testOutput/simulation1TramMetronet" + std::to_string(fileCounter) + "MovementLog.txt")
		);

        fileCounter++;
		fileName1 = "_testInput/SimulationOutputTests/simulation1TramMetronet" + std::to_string(fileCounter) + ".xml";
	    fileName2 = "_testInput/SimulationOutputTests/simulation1TramPassagiers" + std::to_string(fileCounter) + ".xml";
	}
    EXPECT_TRUE(fileCounter-1 == 3);
}

TEST_F(MetroNetOutputTest, SimulationMeerdereTramsPerLijnNoErrors) {

	std::ofstream errors;
    std::ofstream initOverview;
    std::ofstream initMap;
    std::ofstream postOverview;
    std::ofstream postMap;
    std::ofstream movement;
    int fileCounter = 1;
    std::string fileName1 = "_testInput/SimulationOutputTests/simulation+1TramMetronet" + std::to_string(fileCounter) + ".xml";
    std::string fileName2 = "_testInput/SimulationOutputTests/simulation+1TramPassagiers" + std::to_string(fileCounter) + ".xml";

    while (FileExists(fileName1) && FileExists(fileName2)) {
		SetUp();
		errors.open("_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "ErrorLog.txt");
		initOverview.open("_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "InitOverview.txt");
		initMap.open("_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "InitMap.txt");
		postOverview.open("_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "PostOverview.txt");
		postMap.open("_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "PostMap.txt");
		movement.open("_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "MovementLog.txt");
        MetroNetImporter::importMetroNet(fileName1.c_str(), errors, *metronet);
		MetroNetImporter::importPassengers(fileName2.c_str(), errors, *metronet);
		metronet->writeToOutputStream(initOverview);
		metronet->drawToOutputStream(initMap);
		metronet->runSimulation(movement);
		metronet->writeToOutputStream(postOverview);
		metronet->drawToOutputStream(postMap);
        errors.close();
        initOverview.close();
        initMap.close();
        postOverview.close();
        postMap.close();
        movement.close();

		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation+1TramMetronet" + std::to_string(fileCounter) + "ErrorLogExpected.txt",
			"_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "ErrorLog.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation+1TramMetronet" + std::to_string(fileCounter) + "InitOverviewExpected.txt",
			"_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "InitOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation+1TramMetronet" + std::to_string(fileCounter) + "InitMapExpected.txt",
			"_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "InitMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation+1TramMetronet" + std::to_string(fileCounter) + "PostOverviewExpected.txt",
			"_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "PostOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation+1TramMetronet" + std::to_string(fileCounter) + "PostMapExpected.txt",
			"_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "PostMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulation+1TramMetronet" + std::to_string(fileCounter) + "MovementLogExpected.txt",
			"_testOutput/simulation+1TramMetronet" + std::to_string(fileCounter) + "MovementLog.txt")
		);

        fileCounter++;
		fileName1 = "_testInput/SimulationOutputTests/simulation+1TramMetronet" + std::to_string(fileCounter) + ".xml";
	    fileName2 = "_testInput/SimulationOutputTests/simulation+1TramPassagiers" + std::to_string(fileCounter) + ".xml";
	}
    EXPECT_TRUE(fileCounter-1 == 4);
}

TEST_F(MetroNetOutputTest, SimulationTramsOverloaded) {

	std::ofstream errors;
    std::ofstream initOverview;
    std::ofstream initMap;
    std::ofstream postOverview;
    std::ofstream postMap;
    std::ofstream movement;
    int fileCounter = 1;
    std::string fileName1 = "_testInput/SimulationOutputTests/simulationOverloadMetronet" + std::to_string(fileCounter) + ".xml";
    std::string fileName2 = "_testInput/SimulationOutputTests/simulationOverloadPassagiers" + std::to_string(fileCounter) + ".xml";

    while (FileExists(fileName1) && FileExists(fileName2)) {
		SetUp();
		errors.open("_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "ErrorLog.txt");
		initOverview.open("_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "InitOverview.txt");
		initMap.open("_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "InitMap.txt");
		postOverview.open("_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "PostOverview.txt");
		postMap.open("_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "PostMap.txt");
		movement.open("_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "MovementLog.txt");
        MetroNetImporter::importMetroNet(fileName1.c_str(), errors, *metronet);
		MetroNetImporter::importPassengers(fileName2.c_str(), errors, *metronet);
		metronet->writeToOutputStream(initOverview);
		metronet->drawToOutputStream(initMap);
		metronet->runSimulation(movement);
		metronet->writeToOutputStream(postOverview);
		metronet->drawToOutputStream(postMap);
        errors.close();
        initOverview.close();
        initMap.close();
        postOverview.close();
        postMap.close();
        movement.close();

		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationOverloadMetronet" + std::to_string(fileCounter) + "ErrorLogExpected.txt",
			"_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "ErrorLog.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationOverloadMetronet" + std::to_string(fileCounter) + "InitOverviewExpected.txt",
			"_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "InitOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationOverloadMetronet" + std::to_string(fileCounter) + "InitMapExpected.txt",
			"_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "InitMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationOverloadMetronet" + std::to_string(fileCounter) + "PostOverviewExpected.txt",
			"_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "PostOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationOverloadMetronet" + std::to_string(fileCounter) + "PostMapExpected.txt",
			"_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "PostMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationOverloadMetronet" + std::to_string(fileCounter) + "MovementLogExpected.txt",
			"_testOutput/simulationOverloadMetronet" + std::to_string(fileCounter) + "MovementLog.txt")
		);

        fileCounter++;
		fileName1 = "_testInput/SimulationOutputTests/simulationOverloadMetronet" + std::to_string(fileCounter) + ".xml";
	    fileName2 = "_testInput/SimulationOutputTests/simulationOverloadPassagiers" + std::to_string(fileCounter) + ".xml";
	}
    EXPECT_TRUE(fileCounter-1 == 3);
}

TEST_F(MetroNetOutputTest, SimulationInfLoop) {

	std::ofstream errors;
    std::ofstream initOverview;
    std::ofstream initMap;
    std::ofstream postOverview;
    std::ofstream postMap;
    std::ofstream movement;
    int fileCounter = 1;
    std::string fileName1 = "_testInput/SimulationOutputTests/simulationInfLoopMetronet" + std::to_string(fileCounter) + ".xml";
    std::string fileName2 = "_testInput/SimulationOutputTests/simulationInfLoopPassagiers" + std::to_string(fileCounter) + ".xml";

    while (FileExists(fileName1) && FileExists(fileName2)) {
		SetUp();
		errors.open("_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "ErrorLog.txt");
		initOverview.open("_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "InitOverview.txt");
		initMap.open("_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "InitMap.txt");
		postOverview.open("_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "PostOverview.txt");
		postMap.open("_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "PostMap.txt");
		movement.open("_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "MovementLog.txt");
        MetroNetImporter::importMetroNet(fileName1.c_str(), errors, *metronet);
		MetroNetImporter::importPassengers(fileName2.c_str(), errors, *metronet);
		metronet->writeToOutputStream(initOverview);
		metronet->drawToOutputStream(initMap);
		metronet->runSimulation(movement);
		metronet->writeToOutputStream(postOverview);
		metronet->drawToOutputStream(postMap);
        errors.close();
        initOverview.close();
        initMap.close();
        postOverview.close();
        postMap.close();
        movement.close();

		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationInfLoopMetronet" + std::to_string(fileCounter) + "ErrorLogExpected.txt",
			"_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "ErrorLog.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationInfLoopMetronet" + std::to_string(fileCounter) + "InitOverviewExpected.txt",
			"_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "InitOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationInfLoopMetronet" + std::to_string(fileCounter) + "InitMapExpected.txt",
			"_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "InitMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationInfLoopMetronet" + std::to_string(fileCounter) + "PostOverviewExpected.txt",
			"_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "PostOverview.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationInfLoopMetronet" + std::to_string(fileCounter) + "PostMapExpected.txt",
			"_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "PostMap.txt")
		);
		EXPECT_TRUE(FileCompare(
			"_testOutput/SimulationOutputTestsExpected/simulationInfLoopMetronet" + std::to_string(fileCounter) + "MovementLogExpected.txt",
			"_testOutput/simulationInfLoopMetronet" + std::to_string(fileCounter) + "MovementLog.txt")
		);

        fileCounter++;
		fileName1 = "_testInput/SimulationOutputTests/simulationInfLoopMetronet" + std::to_string(fileCounter) + ".xml";
	    fileName2 = "_testInput/SimulationOutputTests/simulationInfLoopPassagiers" + std::to_string(fileCounter) + ".xml";
	}
    EXPECT_TRUE(fileCounter-1 == 1);
}
