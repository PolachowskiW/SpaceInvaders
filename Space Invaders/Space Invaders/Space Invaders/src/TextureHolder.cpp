#include "TextureHolder.h"
// Include the "assert feature"

#include <assert.h>
TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}
	{
		return keyValuePair -> second;
	}
	{
		auto& texture = m[filename];
		texture.loadFromFile(filename);

		return texture;
	}