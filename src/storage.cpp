#include "../headers/storage.h"

#include <fstream>
#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;

std::string store::readfromDB(std::string dbFilePath, long loc) {
	std::ifstream fio;
	fio.open(dbFilePath);
	fio.seekg(loc);
	char byte = 0;
	short size = 0;
	fio >> size;
	std::string doc(size, ' ');
	fio.read(&doc[0], size);
	fio >> byte;
	return doc;
};

long store::writeToDB(std::string dbFilePath, std::string data) {
	std::ofstream fio;
	fio.open(dbFilePath, std::ios::ate|std::ios::app);
	short size = data.size()+1;
	long curLoc = fio.tellp();
	fio << size << " " << data << '~';
	fio.close();
	return curLoc;
};

void store::loadIndex(std::string indexFile, std::unordered_map<std::string, long>& index) {
	std::ifstream fio;
	fio.open(indexFile);
	std::string key, value;
	while (!fio.eof()) {
		fio >> key;
		fio >> value;
		if (key.empty()) break;
		index[key]= std::stol(value);
	}
};

void store::writeToIndex(std::string indexFile, std::string id, long pos) {
	std::ofstream fio;
	fio.open(indexFile, std::ios::ate | std::ios::app);
	fio << id << " " << pos << std::endl;
	fio.close();
};

void store::deleteFolder(std::string folderPath) {
	fs::remove(folderPath);
};

void store::makeDir(std::string folderName) {
	fs::create_directory(folderName);
}





