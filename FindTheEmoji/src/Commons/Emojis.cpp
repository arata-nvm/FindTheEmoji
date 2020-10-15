#include "Commons/Emojis.hpp"

Texture Emojis::GetEmojiTexture(const char32 emoji) {
	auto it = textures.find(emoji);
	if (it != textures.end()) {
		return it->second;
	}
	Texture tex = Texture(Emoji(Format(emoji)));
	textures.emplace(emoji, tex);
	Logger.writeln(U"Created texture: " + Format(emoji));
	return tex;
}

Array<char32> Emojis::RandomEmojis(const int num) {
	return Range(U'😀', U'🙄').asArray().shuffled().take(num);
}
