#pragma once
#include <map>
#include <Siv3D.hpp>

static std::map<char32, Texture> textures;

class Emojis {
public:
	static Texture GetEmojiTexture(char32 emoji);

	static Array<char32> RandomEmojis(int);
};