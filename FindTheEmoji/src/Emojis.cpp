#include "Emojis.hpp"

Texture Emojis::getEmojiTexture(char32 emoji) {
	std::map<char32, Texture>::iterator it = textures.find(emoji);
	if (it != textures.end()) {
		return it->second;
	}
	Texture tex = Texture(Emoji(Format(emoji)));
	textures.emplace(emoji, tex);
	Logger.writeln(U"Created texture: " + Format(emoji));
	return tex;
}