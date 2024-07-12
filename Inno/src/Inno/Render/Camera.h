#pragma once

#include <glm/glm.hpp>

namespace Inno
{
	class Camera
	{
	public:
		Camera();
		virtual ~Camera() = default;

		/**
		 * @brief Gets the rotation of the camera.
		 */
		inline const glm::vec3& GetRotation() const { return m_Rotation; }
		/**
		 * @brief Sets the rotation of the camera.
		 * @param rotation The new rotation of the camera.
		 */
		inline void SetRotation(const glm::vec3 rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		/**
		 * @brief Gets the position of the camera.
		 */
		inline const glm::vec3& GetPosition() const { return m_Position; }
		/**
		 * @brief Sets the position of the camera.
		 * @param position The new position of the camera.
		 */
		inline void SetPosition(const glm::vec3 position) { m_Position = position; RecalculateViewMatrix(); }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		/**
		 * @brief Retrieves the view matrix of the camera.
		 */
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		/**
		 * @brief Retrieves the view projection matrix of the camera.
		 */
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		glm::vec3 m_Rotation = { 0.0f,0.0f,0.0f };

	protected:
		void RecalculateViewMatrix();
	
	private:
		void SetViewProjectionMatrix();
	};


	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float leftB, float rightB, float bottomB, float topB);
	};
}

