#include "Texture.h"
#include <SOIL2/SOIL2.h>

Texture::Texture(const std::string& path)
	: m_RenderID(0), m_FilePath(path), m_localBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	//stbi_set_flip_vertically_on_load(1);
	m_RenderID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RenderID);
	glBindTexture(GL_TEXTURE_2D, 0);
	/*m_localBuffer = SOIL_load_image(path.c_str(), &m_Width, &m_Height, 0, SOIL_LOAD_RGBA);
	GLCALL(glGenTextures(1, &m_RenderID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_localBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_localBuffer)
		SOIL_free_image_data(m_localBuffer);*/
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &m_RenderID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}

void Texture::Unbind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

