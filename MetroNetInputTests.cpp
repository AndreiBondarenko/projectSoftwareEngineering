#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

#include "MetroNet.h"
#include "MetroNetUtils.h"
#include "MetroNetImporter.h"

class MetroNetInputTests: public ::testing::Test {
protected:
	friend class MetroNet;

	virtual void SetUp() {
		delete metronet;
		metronet = new MetroNet();
	}

	MetroNet* metronet = new MetroNet();
};

TEST_F(MetroNetInputTests, InputHappyDay) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/MetroNetInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));

	std::ofstream ofile;
	SuccessEnum importResult;

	ofile.open("_testInput/MetroNetInputTests/correctInput.xml");
	ofile << "<?xml version=\"1.0\" ?>" << std::endl
		<< "<METRONET>\n\t<STATION>\n"
		<< "\t\t<naam>A</naam>\n\t\t<type>Metrostation</type>\n"
		<< "\t\t<SPOOR>\n\t\t\t<spoor>12</spoor>\n"
		<< "\t\t\t<volgende>B</volgende>\n\t\t\t<vorige>B</vorige>\n"
		<< "\t\t</SPOOR>\n\t</STATION>\n\t<STATION>\n"
		<< "\t\t<naam>B</naam>\n\t\t<type>Halte</type>\n"
		<< "\t\t<SPOOR>\n\t\t\t<spoor>12</spoor>\n"
		<< "\t\t\t<volgende>A</volgende>\n\t\t\t<vorige>A</vorige>\n"
		<< "\t\t</SPOOR>\n\t</STATION>\n\t<TRAM>\n"
		<< "\t\t<lijnNr>12</lijnNr>\n\t\t<zitplaatsen>32</zitplaatsen>\n"
		<< "\t\t<snelheid>60</snelheid>\n\t\t<beginStation>A</beginStation>\n"
		<< "\t\t<type>PCC</type>\n\t\t<voertuigNr>1</voertuigNr>\n"
		<< "\t</TRAM>\n</METRONET>" << std::endl;
	ofile.close();
	ofile.open("_testOutput/metronetInputTestsError.txt");
	importResult = MetroNetImporter::importMetroNet("_testInput/MetroNetInputTests/correctInput.xml", ofile, *metronet);
	ofile.close();
	EXPECT_TRUE(importResult == Success);
	EXPECT_TRUE(FileIsEmpty("_testOutput/metronetInputTestsError.txt"));
}

TEST_F(MetroNetInputTests, correctInput) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/MetroNetInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));

	std::ofstream ofile;
	SuccessEnum importResult;
	int fileCounter = 1;
	std::string fileName = "_testInput/MetroNetInputTests/correctInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		ofile.open("_testOutput/metronetInputTestsError.txt");
		importResult = MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == Success);
		EXPECT_TRUE(FileIsEmpty("_testOutput/metronetInputTestsError.txt"));

		fileCounter++;
		fileName = "_testInput/MetroNetInputTests/correctInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 2);
}

TEST_F(MetroNetInputTests, wrongInputSyntaxError) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/MetroNetInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/MetroNetInputTestsExpected"));

	std::ofstream ofile;
	SuccessEnum importResult;
	int fileCounter = 1;
	std::string fileName = "_testInput/MetroNetInputTests/syntaxErrorInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		ofile.open("_testOutput/metronetInputTestsError.txt");
		importResult = MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == ImportAborted);
		std::string expectedFileName = "_testOutput/MetroNetInputTestsExpected/syntaxError" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/metronetInputTestsError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/MetroNetInputTests/syntaxErrorInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 6);
}

TEST_F(MetroNetInputTests, wrongInputNoCrash) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/MetroNetInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/MetroNetInputTestsExpected"));

	std::ofstream ofile;
	SuccessEnum importResult;
	int fileCounter = 34;
	std::string fileName = "_testInput/MetroNetInputTests/wrongInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		ofile.open("_testOutput/metronetInputTestsError.txt");
		importResult = MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == PartialImport);
		std::string expectedFileName = "_testOutput/MetroNetInputTestsExpected/wrongInput" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/metronetInputTestsError.txt", expectedFileName));
		fileCounter++;
		fileName = "_testInput/MetroNetInputTests/wrongInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 41);
}

TEST_F(MetroNetInputTests, inconsistent) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/MetroNetInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/MetroNetInputTestsExpected"));

	std::ofstream ofile;
	int fileCounter = 1;
	std::string fileName = "_testInput/MetroNetInputTests/inconsistent" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		ofile.open("_testOutput/metronetInputTestsError.txt");
		EXPECT_DEATH(MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet), "MetroNet is inconsistent");
		ofile.close();
		std::string expectedFileName = "_testOutput/MetroNetInputTestsExpected/inconsistent" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/metronetInputTestsError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/MetroNetInputTests/inconsistent" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 7);
}

TEST_F(MetroNetInputTests, wrongInputCrash) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/MetroNetInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/MetroNetInputTestsExpected"));

	std::string errors[3] = 
		{
		"BeginStation of newTram isn't empty", 
		"This MetroNet already contains a Tram with this voertuigNr",
		"This MetroNet already contains a station with this name"
		};

	std::ofstream ofile;
	int fileCounter = 1;
	std::string fileName = "_testInput/MetroNetInputTests/crashInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		ofile.open("_testOutput/metronetInputTestsError.txt");
		EXPECT_DEATH(MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet), errors[fileCounter-1]);
		ofile.close();
		std::string expectedFileName = "_testOutput/MetroNetInputTestsExpected/crash" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/metronetInputTestsError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/MetroNetInputTests/crashInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 4);
}

TEST_F(MetroNetInputTests, multipleWrongInputs) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/MetroNetInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/MetroNetInputTestsExpected"));

	std::ofstream ofile;
	SuccessEnum importResult;
	int fileCounter = 1;
	std::string fileName = "_testInput/MetroNetInputTests/multipleWrongInputs" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		ofile.open("_testOutput/metronetInputTestsError.txt");
		importResult = MetroNetImporter::importMetroNet(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == PartialImport);
		std::string expectedFileName = "_testOutput/MetroNetInputTestsExpected/multipleWrongInputs" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/metronetInputTestsError.txt", expectedFileName));
		fileCounter++;
		fileName = "_testInput/MetroNetInputTests/multipleWrongInputs" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 7);
}