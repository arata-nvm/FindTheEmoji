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

	int getRank(int score) const;

	int getHighScore() const;

	int scoresCount() const;

	void saveRanking() const;

	void loadRanking();


};

