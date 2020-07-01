#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 tar);
	glm::mat4 get_view_matrix();
	glm::mat4 get_model_matrix(glm::vec3 model_trans);
	glm::mat4 get_projection_matrix();

private:
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_dir;
	int m_width;
	int m_height;
	float m_fov;
	float m_zNear;
	float m_zFar;
};

Camera::Camera(glm::vec3 pos, glm::vec3 tar) 
	: m_pos(pos), m_target(tar), m_fov(45.0f), m_width(1600), m_height(1200), m_zNear(0.1f), m_zFar(50.0f)
{
	m_dir = glm::normalize(tar - pos);
}

inline glm::mat4 Camera::get_view_matrix()
{
	return glm::translate(glm::mat4(1.0f), -m_pos);
}

inline glm::mat4 Camera::get_model_matrix(glm::vec3 model_trans)
{
	return glm::translate(glm::mat4(1.0f), model_trans);
}

inline glm::mat4 Camera::get_projection_matrix()
{
	float aspect = float(m_width) / float(m_height);
	float fov_rad = 3.14 / 180 * m_fov;
	return glm::perspective(fov_rad, aspect, m_zNear, m_zFar);
}

