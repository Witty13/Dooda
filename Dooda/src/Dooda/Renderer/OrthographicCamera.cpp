#include "Ddpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dooda 
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: d_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), d_viewMatrix(1.0f)
	{
		d_viewProjectionMatrix = d_projectionMatrix * d_viewMatrix;
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		d_position = position; 
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(const float rotation)
	{
		d_rotation = rotation * 57.3f;  //Make this work without the fixing?  57.3 works
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), d_position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(d_rotation), glm::vec3 (0.0f, 0.0f, 1.0f));

		d_viewMatrix = glm::inverse(transform);
		d_viewProjectionMatrix = d_projectionMatrix * d_viewMatrix;
	}

}