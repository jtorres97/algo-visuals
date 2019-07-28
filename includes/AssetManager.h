#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <map>

class AssetManager
{
public:
	AssetManager();

	static sf::Font &GetFont(std::string const &filename);
	static sf::SoundBuffer &GetSoundBuffer(std::string const &filename);
private:
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	static AssetManager *s_instance;
};
