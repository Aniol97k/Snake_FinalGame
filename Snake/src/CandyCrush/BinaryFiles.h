#pragma once
#include "iostream"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::ios;

namespace BinaryFiles {

	struct HighScores
	{
		std::string name;
		int score;

	};

	HighScores bests[10];

	void sort() {
		HighScores sortRank;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (bests[i].score > bests[i].score) {
					sortRank = bests[i];
					bests[i] = bests[j];
					bests[j] = sortRank;
				}
			}
		}
	}

	void setNewRank(HighScores &newRank) {
		for (int i = 0; i < 10; i++) {
			if (bests[i].score < newRank.score) {
				for (int j = 10 - 1; j > i; j--) {
					bests[j] = bests[j - 1];
				}
				bests[i] = newRank;
				break;
			}
		}
	}

	void writeBin(std::string &name, int score) {

		std::ifstream readFile("../../res/Ranking.bin", ios::binary);

		for (int i = 0; i < 10; i++) {
			std::getline(readFile, bests[i].name, '\0');
			readFile.read(reinterpret_cast<char*>(&bests[i].score), sizeof(bests[i].score));
		}

		readFile.close();

		HighScores toIns;
		toIns.name = name;
		toIns.score = score;

		sort();
		setNewRank(toIns);

		std::ofstream writeFile("../../res/Ranking.bin", ios::binary);

		for (int i = 0; i < 10; i++) {

			writeFile.write(bests[i].name.c_str(), bests[i].name.size());
			writeFile.write("\0", sizeof(char));
			writeFile.write(reinterpret_cast<char*>(&bests[i].score), sizeof(bests[i].score));
		}

		writeFile.close();
	}

	void readBin() {
		std::ifstream readFile("../../res/Ranking.bin", ios::binary);

		std::vector<HighScores> retRank;
		for (int i = 0; i < 1; i++) {
			std::getline(readFile, retRank[i].name, '\0');
			readFile.read(reinterpret_cast<char*>(&retRank[i].score), sizeof(retRank[i].score));
			
		}

		for (int i = 0; i < 10; ++i) {
			std::cout << "Name: " << retRank[i].name << "and score: " << retRank[i].score;
		}
		readFile.close();
		//return retRank;




	}
}
