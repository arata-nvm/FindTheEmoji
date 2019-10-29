#pragma once
#include <Siv3D.hpp>

class Ranking
{
private:
	Array<int> ranks;

	String fileName;

public:
	Ranking(String _fileName);

	int addScore(int score);

	int getRank(int score);

	int getHighScore();

	int size();

	void saveRanking();

	void loadRanking();


};

