#include "AssetManager.h"

AssetManager *AssetManager::s_instance = nullptr;

AssetManager::AssetManager()
{
	s_instance = this;
}

sf::Font &AssetManager::GetFont(std::string const &filename)
{
	auto &fontMap = s_instance->m_fonts;
	auto pairFound = fontMap.find(filename);

	if (pairFound != fontMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto &font = fontMap[filename];
		font.loadFromFile(filename);
		return font;
	}
}

sf::SoundBuffer &AssetManager::GetSoundBuffer(std::string const & filename)
{
	auto &sBufferMap = s_instance->m_soundBuffers;
	auto pairFound = sBufferMap.find(filename);

	if (pairFound != sBufferMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto &sBuffer = sBufferMap[filename];
		sBuffer.loadFromFile(filename);
		return sBuffer;
	}
}
