#pragma once
#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class Model
{
public:
	Model(const std::string& filepath);

private:
	std::string m_FilePath;
	std::vector<float> m_vb;
	std::vector<unsigned int> m_ib;
	VertexBufferLayout m_layout;
	void ParseFile(const std::string& filepath);

public:
	inline std::vector<float> GetVbData() const { return m_vb; }
	inline std::vector<unsigned int> GetIbData() const { return m_ib; }
	inline VertexBufferLayout GetLayout() const { return m_layout; }
};

