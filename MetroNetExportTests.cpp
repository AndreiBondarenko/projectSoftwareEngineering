#include <gtest/gtest.h>

#include "MetroNet.h"
#include "MetroNetImporter.h"
#include "MetroNetUtils.h"


class MetroNetExportTest: public ::testing::Test {
protected:
	friend class MetroNet;
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	Tram tram;
	Station station;
    MetroNet metronet;

};

TEST_F(MetroNetExportTest, FileCompareTest) {
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

TEST_F(MetroNetExportTest, OutputHappyDayTest01) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    std::ofstream output;
    std::ofstream movement;
    errors.open("_testOutput/happyDay01ErrorLog.txt");
    output.open("_testOutput/happyDay01.txt");
    movement.open("_testOutput/happyDay01MovementLog.txt");
    MetroNetImporter::importMetroNet("_testInput/happyDay01.xml", errors, metronet);
    metronet.writeToOutputStream(output);
    output.close();
    errors.close();
    movement.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/happyDay01Expected.txt", "_testOutput/happyDay01.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/happyDay01MovementLogExpected.txt", "_testOutput/happyDay01MovementLog.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/happyDay01ErrorLogExpected.txt", "_testOutput/happyDay01ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputHappyDayTest02) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    std::ofstream output;
    std::ofstream movement;
    errors.open("_testOutput/happyDay02ErrorLog.txt");
    output.open("_testOutput/happyDay02.txt");
    movement.open("_testOutput/happyDay02MovementLog.txt");
    MetroNetImporter::importMetroNet("_testInput/happyDay02.xml", errors, metronet);
    metronet.writeToOutputStream(output);
    for (int n = 1; n <= 5; n++) {
        movement << n << ".\n";
        std::set<int> alreadyMoved;
        for (auto mapIt = metronet.getAlleStations()->begin(); mapIt != metronet.getAlleStations()->end(); mapIt++) {
            if (mapIt->second->isTramInStation() && alreadyMoved.find(mapIt->second->getSpoor()) == alreadyMoved.end()) {
                alreadyMoved.insert(mapIt->second->getSpoor());
                metronet.moveTram(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement);
                metronet.movePassengers(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement, errors);
                movement << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            }
        }
    }
    movement.close();
    output.close();
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/happyDay02MovementLogExpected.txt", "_testOutput/happyDay02MovementLog.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/happyDay02Expected.txt", "_testOutput/happyDay02.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/happyDay02ErrorLogExpected.txt", "_testOutput/happyDay02ErrorLog.txt"));


}

TEST_F(MetroNetExportTest, OutputBadDayTest01InsufficientPassengers) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    std::ofstream output;
    std::ofstream movement;
    errors.open("_testOutput/badDay01ErrorLog.txt");
    output.open("_testOutput/badDay01.txt");
    movement.open("_testOutput/badDay01MovementLog.txt");
    MetroNetImporter::importMetroNet("_testInput/badDay01.xml", errors, metronet);
    metronet.writeToOutputStream(output);
    for (int n = 1; n <= 5; n++) {
        movement << n << ".\n";
        std::set<int> alreadyMoved;
        for (auto mapIt = metronet.getAlleStations()->begin(); mapIt != metronet.getAlleStations()->end(); mapIt++) {
            if (mapIt->second->isTramInStation() && alreadyMoved.find(mapIt->second->getSpoor()) == alreadyMoved.end()) {
                alreadyMoved.insert(mapIt->second->getSpoor());
                metronet.moveTram(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement);
                metronet.movePassengers(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement, errors);
                movement << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            }
        }
    }
    movement.close();
    output.close();
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay01MovementLogExpected.txt", "_testOutput/badDay01MovementLog.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay01Expected.txt", "_testOutput/badDay01.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay01ErrorLogExpected.txt", "_testOutput/badDay01ErrorLog.txt"));

}

TEST_F(MetroNetExportTest, OutputBadDayTest02MaxCapacityExceeded) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    std::ofstream output;
    std::ofstream movement;
    errors.open("_testOutput/badDay02ErrorLog.txt");
    output.open("_testOutput/badDay02.txt");
    movement.open("_testOutput/badDay02MovementLog.txt");
    MetroNetImporter::importMetroNet("_testInput/badDay02.xml", errors, metronet);
    metronet.writeToOutputStream(output);
    for (int n = 1; n <= 5; n++) {
        movement << n << ".\n";
        std::set<int> alreadyMoved;
        for (auto mapIt = metronet.getAlleStations()->begin(); mapIt != metronet.getAlleStations()->end(); mapIt++) {
            if (mapIt->second->isTramInStation() && alreadyMoved.find(mapIt->second->getSpoor()) == alreadyMoved.end()) {
                alreadyMoved.insert(mapIt->second->getSpoor());
                metronet.moveTram(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement);
                metronet.movePassengers(mapIt->second->getVolgende(), mapIt->second->getSpoor(), movement, errors);
                movement << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            }
        }
    }
    movement.close();
    output.close();
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay02MovementLogExpected.txt", "_testOutput/badDay02MovementLog.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay02Expected.txt", "_testOutput/badDay02.txt"));
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay02ErrorLogExpected.txt", "_testOutput/badDay02ErrorLog.txt"));

}

TEST_F(MetroNetExportTest, OutputBadDayTest03ImportAborted) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay03ErrorLog.txt");
    MetroNetImporter::importMetroNet("_testInput/badDay03.xml", errors, metronet);
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay03ErrorLogExpected.txt", "_testOutput/badDay03ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest04NoRoot) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay04ErrorLog.txt");
    MetroNetImporter::importMetroNet("_testInput/badDay04.xml", errors, metronet);
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay04ErrorLogExpected.txt", "_testOutput/badDay04ErrorLog.txt"));

}

TEST_F(MetroNetExportTest, OutputBadDayTest05NoStationNaam) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay05ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay05.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay05ErrorLogExpected.txt", "_testOutput/badDay05ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest06NoStationVolgende) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay06ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay06.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay06ErrorLogExpected.txt", "_testOutput/badDay06ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest07NoStationVorige) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay07ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay07.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay07ErrorLogExpected.txt", "_testOutput/badDay07ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest08NoStationSpoor) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay08ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay08.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay08ErrorLogExpected.txt", "_testOutput/badDay08ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest09EmptyStationNaam) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay09ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay09.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay09ErrorLogExpected.txt", "_testOutput/badDay09ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest10EmptyStationVolgende) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay10ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay10.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay10ErrorLogExpected.txt", "_testOutput/badDay10ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest11EmptyStationVorige) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay11ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay11.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay11ErrorLogExpected.txt", "_testOutput/badDay11ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest12EmptyStationSpoor) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay12ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay12.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay12ErrorLogExpected.txt", "_testOutput/badDay12ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest13InvalidStationSpoor) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay13ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay13.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay13ErrorLogExpected.txt", "_testOutput/badDay13ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest14NegativeStationSpoor) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay14ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay14.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay14ErrorLogExpected.txt", "_testOutput/badDay14ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest15InvalidStationOpstappen) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay15ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay15.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay15ErrorLogExpected.txt", "_testOutput/badDay15ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest16NegativeStationOpstappen) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay16ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay16.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay16ErrorLogExpected.txt", "_testOutput/badDay16ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest17InvalidStationAfstappen) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay17ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay17.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay17ErrorLogExpected.txt", "_testOutput/badDay17ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest18NegativeStationAfstappen) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay18ErrorLog.txt");
    EXPECT_DEATH(MetroNetImporter::importMetroNet("_testInput/badDay18.xml", errors, metronet), "MetroNet is inconsistent");
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay18ErrorLogExpected.txt", "_testOutput/badDay18ErrorLog.txt"));
}

TEST_F(MetroNetExportTest, OutputBadDayTest19UnknownElement) {
    ASSERT_TRUE(DirectoryExists("_testOutput"));
    ASSERT_TRUE(DirectoryExists("_testInput"));
    std::ofstream errors;
    errors.open("_testOutput/badDay19ErrorLog.txt");
    MetroNetImporter::importMetroNet("_testInput/badDay19.xml", errors, metronet);
    errors.close();
    EXPECT_TRUE(FileCompare("_testOutput/expected/badDay19ErrorLogExpected.txt", "_testOutput/badDay19ErrorLog.txt"));
}
