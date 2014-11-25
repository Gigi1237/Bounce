#ifndef TEXTURE_H
#define TEXTURE_H

#include "basic.h"
#include <stb_image.h>


class Texture
{
public:
	Texture(const std::string& fileName);
	void Bind();
	virtual ~Texture();
private:
	unsigned int m_texture;
};

#endif