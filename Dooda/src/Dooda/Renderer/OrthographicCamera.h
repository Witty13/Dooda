#pragma once

#include <glm/glm.hpp>

namespace Dooda {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera();

		const glm::vec3& GetPosition() const { return d_position; }
		void SetPosition(const glm::vec3& position);

		float GetRotation() const { return d_rotation; }
		void SetRotation(const float rotation);

		const glm::mat4& GetProjectionMatrix() const { return d_projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return d_viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return d_viewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 d_projectionMatrix;
		glm::mat4 d_viewMatrix;
		glm::mat4 d_viewProjectionMatrix;

		glm::vec3 d_position = glm::vec3( 0.0f, 0.0f, 0.0f );
		float d_rotation = 0.0f;
	};

}
