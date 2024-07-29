#include "pch.h"
#include "Camera.h"

#include "Inno/Render/Renderer.h"
#include "Inno/Core/Timestep.h"
#include "Inno/Input/Input.h"
#include "Inno/Input/Mousecode.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Inno
{
	////////////////* Camera Interface Lies Here *////////////////

	Camera::Camera(float aspectRatio)
		: m_AspectRatio(aspectRatio), m_ZoomLevel(1.0f), m_ViewMatrix(1.0f)
	{
		SetViewProjectionMatrix();
	}

	void Camera::SetViewProjectionMatrix()
	{
        switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				// Temporary not support None API case
				INNO_CORE_ASSERT(false, "RendererAPI::None current not supported!");
				m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
				break;
			}
			case RendererAPI::API::OpenGL:
			{
				m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
				break;
			}
			default:
			{
				INNO_CORE_ASSERT(false, "Unknown RendererAPI!");
				m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
				break;
			}
		}
	}

	void Camera::Recalculate()
	{
		/* Apply rotations in the order Z, Y, X */
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		// Caculate View Projection Matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

		transform = rotationMatrix * transform;

		m_ViewMatrix = glm::inverse(transform);
		SetViewProjectionMatrix();
	}

	void Camera::OnUpdate()
	{
		static bool holding = false;

		if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
		{
			static glm::vec2 previousMousePos(0.0f);

			glm::vec2 currentMousePos = Input::GetMousePosition();
			glm::vec2 mouseDelta = holding ? currentMousePos - previousMousePos : glm::vec2(0.0f);
			glm::vec3 moveDelta = glm::vec4(mouseDelta.x, -mouseDelta.y, 0.0f, 0.0f);

			m_Position -= moveDelta * m_TranslationSpeed * m_ZoomLevel * Timestep::GetDeltaTimeSeconds();

			Recalculate();

			holding = true;
			previousMousePos = currentMousePos;
		}
		else
		{
			holding = false;
		}
	}

	void Camera::OnEvent(Event& event)
	{
		event.Dispatch<MouseScrolledEvent>(BIND_FUNC(Camera::OnMouseScrolled, this));
	}

	void Camera::Resize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);
		SetViewProjectionMatrix();
	}

	bool Camera::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);
		SetViewProjectionMatrix();

		return false;
	}

	////////////////* Camera Implementations Lie Here *////////////////

	OrthographicCamera::OrthographicCamera(float aspectRatio)
		: Camera(aspectRatio)
	{
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);
	}
}


