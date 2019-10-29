#include <Siv3D.hpp>

void Main() {
	const Font font(60, Typeface::Light);
	const Array<char32> chars = Range(U'A', U'Z').asArray().append(Range(U'a', U'z'));
	const String targetText = U"C++/OpenSiv3D";

	Array<int32> counts = targetText.map([](auto) { return Random(20, 60); });
	String randomText = targetText;
	Stopwatch stopwatch(true);

	while (System::Update()) {
		if (MouseL.down()) {
			counts = targetText.map([](auto) { return Random(20, 60); });
		}

		if (stopwatch > 0.05s) {
			for (auto i : step(targetText.size())) {

				if (counts[i]) {
					randomText[i] = chars.choice();
					--counts[i];
				}
				else
				{
					randomText[i] = targetText[i];
				}
			}


			stopwatch.restart();
		}

		Vec2 penPos(40, 190);

		for (const auto& glyph : font(targetText)) {
			const auto glyph2 = font.getGlyph(randomText[glyph.index]);
			glyph2.texture.draw(penPos + glyph2.offset);
			penPos.x += glyph.xAdvance * 1.2;
		}
	}
}