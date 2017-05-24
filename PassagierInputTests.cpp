#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

#include "MetroNet.h"
#include "MetroNetUtils.h"
#include "MetroNetImporter.h"

class PassagierInputTests: public ::testing::Test {
protected:
	friend class MetroNet;

	virtual void SetUp() {
		delete metronet;
		metronet = new MetroNet();
	}

	MetroNet* metronet = new MetroNet();	
};

TEST_F(PassagierInputTests, correctInput) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/PassagierInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));

	std::ofstream ofile;
	SuccessEnum importResult;

	int fileCounter = 1;
	std::string fileName = "_testInput/PassagierInputTests/correctInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		importResult = MetroNetImporter::importMetroNet("_testInput/PassagierInputTests/MetroNetInput.xml", ofile, *metronet);
		EXPECT_TRUE(importResult == Success);

		ofile.open("_testOutput/passagierInputTestsError.txt");
		importResult = MetroNetImporter::importPassengers(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == Success);
		EXPECT_TRUE(FileIsEmpty("_testOutput/passagierInputTestsError.txt"));

		fileCounter++;
		fileName = "_testInput/PassagierInputTests/correctInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 3);
}

TEST_F(PassagierInputTests, wrongInputSyntaxError) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/PassagierInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/PassagierInputTestsExpected"));

	std::ofstream ofile;
	SuccessEnum importResult;

	int fileCounter = 1;
	std::string fileName = "_testInput/PassagierInputTests/syntaxErrorInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		importResult = MetroNetImporter::importMetroNet("_testInput/PassagierInputTests/MetroNetInput.xml", ofile, *metronet);
		EXPECT_TRUE(importResult == Success);

		ofile.open("_testOutput/passagierInputTestsError.txt");
		importResult = MetroNetImporter::importPassengers(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == ImportAborted);
		std::string expectedFileName = "_testOutput/PassagierInputTestsExpected/syntaxError" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/passagierInputTestsError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/PassagierInputTests/syntaxErrorInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 6);
}

TEST_F(PassagierInputTests, wrongInputNoCrash) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/PassagierInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/PassagierInputTestsExpected"));

	std::ofstream ofile;
	SuccessEnum importResult;

	int fileCounter = 1;
	std::string fileName = "_testInput/PassagierInputTests/wrongInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		importResult = MetroNetImporter::importMetroNet("_testInput/PassagierInputTests/MetroNetInput.xml", ofile, *metronet);
		EXPECT_TRUE(importResult == Success);

		ofile.open("_testOutput/passagierInputTestsError.txt");
		importResult = MetroNetImporter::importPassengers(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == PartialImport);
		std::string expectedFileName = "_testOutput/PassagierInputTestsExpected/wrongInput" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/passagierInputTestsError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/PassagierInputTests/wrongInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 13);
}

TEST_F(PassagierInputTests, wrongInputCrash) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/PassagierInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/PassagierInputTestsExpected"));

	std::string errors[4] = 
		{
		"Passagier::moveToBeginStation made MetroNet inconsistent",
		"Passagier::moveToBeginStation made MetroNet inconsistent",
		"beginStation is not a station of MetroNet",
		"This MetroNet allready contains a passenger with this name"
		};

	std::ofstream ofile;
	SuccessEnum importResult;

	int fileCounter = 1;
	std::string fileName = "_testInput/PassagierInputTests/crashInput" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		importResult = MetroNetImporter::importMetroNet("_testInput/PassagierInputTests/MetroNetInput.xml", ofile, *metronet);
		EXPECT_TRUE(importResult == Success);

		ofile.open("_testOutput/passagierInputTestsError.txt");
		EXPECT_DEATH(MetroNetImporter::importPassengers(fileName.c_str(), ofile, *metronet), errors[fileCounter-1]);
		ofile.close();
		std::string expectedFileName = "_testOutput/PassagierInputTestsExpected/crash" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/passagierInputTestsError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/PassagierInputTests/crashInput" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 5);
}

TEST_F(PassagierInputTests, multipleWrongInputs) {
	ASSERT_TRUE(DirectoryExists("_testInput"));
	ASSERT_TRUE(DirectoryExists("_testInput/PassagierInputTests"));
	ASSERT_TRUE(DirectoryExists("_testOutput"));
	ASSERT_TRUE(DirectoryExists("_testOutput/PassagierInputTestsExpected"));

	std::ofstream ofile;
	SuccessEnum importResult;

	int fileCounter = 1;
	std::string fileName = "_testInput/PassagierInputTests/multipleWrongInputs" + std::to_string(fileCounter) + ".xml";

	while (FileExists(fileName)) {
		SetUp();
		importResult = MetroNetImporter::importMetroNet("_testInput/PassagierInputTests/MetroNetInput.xml", ofile, *metronet);
		EXPECT_TRUE(importResult == Success);

		ofile.open("_testOutput/passagierInputTestsError.txt");
		importResult = MetroNetImporter::importPassengers(fileName.c_str(), ofile, *metronet);
		ofile.close();
		EXPECT_TRUE(importResult == PartialImport);
		std::string expectedFileName = "_testOutput/PassagierInputTestsExpected/multipleWrongInputs" + std::to_string(fileCounter) + ".txt";
		EXPECT_TRUE(FileCompare("_testOutput/passagierInputTestsError.txt", expectedFileName));

		fileCounter++;
		fileName = "_testInput/PassagierInputTests/multipleWrongInputs" + std::to_string(fileCounter) + ".xml";
	}
	EXPECT_TRUE(fileCounter == 3);
}
