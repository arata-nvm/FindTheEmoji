#pragma once
#include <map>
#include <Siv3D.hpp>

static std::map<char32, Texture> textures;

class Emojis {
public:
	static Texture getEmojiTexture(char32 emoji);
};