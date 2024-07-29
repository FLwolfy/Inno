#pragma once

#include <glm/glm.hpp>

#include "Inno/Event/Event.h"
#include "Inno/Event/ApplicationEvent.h"
#include "Inno/Event/MouseEvent.h"

namespace Inno
{
	class Camera
	{
	public:
		Camera(float aspectRatio = 1280.0f / 720.0f);
		virtual ~Camera() = default;

		/**
		 * @brief This will be called every frame.
		 */
		void OnUpdate();
		/**
		 * @brief Called when an event occurs.
		 * @param event The event that occurred.
		 */
		void OnEvent(Event& event);
		/**
		 * @brief Resize the camera to be the input width and height.
		 */
		void Resize(float width, float height);

		/**
		 * @brief Gets the rotation of the camera.
		 */
		inline const glm::vec3& GetRotation() const { return m_Rotation; }
		/**
		 * @brief Sets the rotation of the camera (in degrees).
		 * @param rotation The new rotation of the camera.
		 */
		inline void SetRotation(const glm::vec3 rotation) { m_Rotation = rotation; Recalculate(); }
		/**
		 * @brief Gets the position of the camera.
		 */
		inline const glm::vec3& GetPosition() const { return m_Position; }
		/**
		 * @brief Sets the position of the camera.
		 * @param position The new position of the camera.
		 */
		inline void SetPosition(const glm::vec3 position) { m_Position = position; Recalculate(); }

		/**
		 * @brief Retrieves the view projection matrix of the camera.
		 */
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
		float m_AspectRatio = 1.0f;
		float m_ZoomLevel = 1.0f;
		float m_TranslationSpeed = 1.0f;
		float m_RotationSpeed = 180.0f;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		glm::vec3 m_Rotation = { 0.0f,0.0f,0.0f };

	protected:
		void Recalculate();
		void SetViewProjectionMatrix();

	private:
		glm::mat4 m_ReverseRotationMatrix = glm::mat4(1.0f);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
	};


	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float aspectRatio);
	};
}

