#include "Commons/Ranking.hpp"

Ranking::Ranking(String _fileName) {
	fileName = _fileName;
}

int Ranking::addScore(int score) {
	ranks.emplace_back(score);
	ranks.sort().reverse();
	return getRank(score);
}

int Ranking::getRank(int score) const {
	int rank = -1;
	ranks.each_index([&](int i, int v) {
		if (v == score) rank = i;
	});
	return rank + 1;
}

int Ranking::getHighScore() const {
	return ranks[0];
}

int Ranking::scoresCount() const {
	return ranks.size();
}

void Ranking::saveRanking() const {
	TextWriter writer(fileName, OpenMode::Trunc, TextEncoding::UTF8);
	for (const auto& rank : ranks) {
		writer.writeln(rank);
	}
	writer.close();
}

void Ranking::loadRanking() {
	TextReader reader(fileName);
	Optional<String> line;
	while (line = reader.readLine()) {
		ranks.emplace_back(Parse<int32>(line.value()));
	}
	reader.close();
	ranks.sort().reverse();
}
