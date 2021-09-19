#pragma once
#include <string>
#include <unordered_map>


namespace store {
	std::string readfromDB(std::string dbFilePath, long location);

	long writeToDB(std::string dbFilePath, std::string data);

	void loadIndex(std::string indexFile, std::unordered_map<std::string, long>& index);

	void writeToIndex(std::string indexFile, std::string id, long pos);

	void deleteFolder(std::string folderPath);

	void makeDir(std::string folderName);

}


