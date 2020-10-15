#pragma once
#include <Siv3D.hpp>

class Ranking
{
private:
	Array<int> ranks;

	String fileName;

public:
	Ranking(const String _fileName);

	int addScore(const int score);

	int getRank(const int score) const;

	int getHighScore() const;

	int scoresCount() const;

	void saveRanking() const;

	void loadRanking();
};

