#include "Ranking.h"

Ranking::Ranking(String _fileName) {
	fileName = _fileName;
}

int Ranking::addScore(int score) {
	ranks.emplace_back(score);
	ranks.sort().reverse();
	return getRank(score);
}

int Ranking::getRank(int score) {
	if (!ranks.includes(score)) this->addScore(score);
	int rank;
	ranks.each_index([&](int i, int v) {
		if (v == score) rank = i;
	});
	return rank + 1;
}

int Ranking::getHighScore() {
	return ranks[0];
}

int Ranking::size() {
	return ranks.size();
}

void Ranking::saveRanking() {
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
