#include <iostream>
#include <fstream>
#include <sstream>

#include "Model.h"

Model::Model(const std::string & filepath)
{
	ParseFile(filepath);
	m_layout.Push<float>(3);
	m_layout.Push<float>(2);
	m_layout.Push<float>(3);
	for (unsigned int i = 0; i < m_vb.size()/8; i++)
	{
		m_ib.push_back(i);
	}
}

void Model::ParseFile(const std::string & filepath)
{
	std::ifstream stream(filepath, std::ifstream::in);
	std::string line;
	std::vector<float> vertex_position;
	std::vector<float> vertex_nornmal;
	std::vector<float> vertex_texcoord;
	while (getline(stream, line))
	{
		if (line.find("#") != std::string::npos)
			continue;
		else if (line.compare(0, 2, "v ") == 0)
		{
			float x, y, z;
			std::stringstream ss(line.erase(0, 1));
			ss >> x; ss >> y; ss >> z;
			vertex_position.push_back(x);
			vertex_position.push_back(y);
			vertex_position.push_back(z);
		}
		else if (line.compare(0, 2, "vt") == 0)
		{
			float x, y;
			std::stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y;
			vertex_texcoord.push_back(x);
			vertex_texcoord.push_back(y);
		}
		else if (line.compare(0, 2, "vn") == 0)
		{
			float x, y, z;
			std::stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y; ss >> z;
			vertex_nornmal.push_back(x);
			vertex_nornmal.push_back(y);
			vertex_nornmal.push_back(z);
		}
		else if (line.compare(0, 2, "f ") == 0)
		{
			std::string pair, v, t, n;
			std::stringstream ss(line.erase(0, 2));
			for (int i = 0; i < 3; i++)
			{
				getline(ss, pair, ' ');
				std::stringstream pairss{ pair };
				getline(pairss, v, '/');
				getline(pairss, t, '/');
				getline(pairss, n, '/');
				int vert = (stoi(v) - 1) * 3;
				int tc = (stoi(t) - 1) * 2;
				int norm = (stoi(n) - 1) * 3;

				m_vb.push_back(vertex_position[vert]);
				m_vb.push_back(vertex_position[vert + 1]);
				m_vb.push_back(vertex_position[vert + 2]);

				m_vb.push_back(vertex_texcoord[tc]);
				m_vb.push_back(vertex_texcoord[tc + 1]);

				m_vb.push_back(vertex_nornmal[norm]);
				m_vb.push_back(vertex_nornmal[norm + 1]);
				m_vb.push_back(vertex_nornmal[norm + 2]);
			}
		}
	}
}

