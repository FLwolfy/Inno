#include "pch.h"
#include "Camera.h"

#include "Inno/Core/Application.h"
#include "Inno/Core/Timestep.h"
#include "Inno/Input/Input.h"
#include "Inno/Input/Mousecode.h"
#include "Inno/Render/Renderer.h"

#include <imgui.h>
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

	void Camera::RecalculateSpeedMultiplier()
	{

	}

	void Camera::RecalculateViewMatrix()
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
		static glm::vec2 previousMousePos(0.0f);
		static glm::vec3 previousCameraPos(0.0f);

		if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			if (!holding)
			{
				holding = true;

				previousMousePos = Input::GetMousePosition();
				previousCameraPos = m_Position;
			}

			glm::vec2 currentMousePos = Input::GetMousePosition();
			glm::vec2 mouseDirection = currentMousePos - previousMousePos;
			glm::vec3 moveDelta = glm::vec3(mouseDirection.x, -mouseDirection.y, 0.0f) * m_ZoomLevel * m_SpeedMultiplier;

			m_Position = previousCameraPos - moveDelta;

			RecalculateViewMatrix();
		}
		else
		{
			holding = false;
		}
	}

	void Camera::OnEvent(Event& event)
	{
		event.Dispatch<MouseScrolledEvent>(BIND_FUNC(Camera::OnMouseScrolled, this));
		event.Dispatch<WindowResizeEvent>(BIND_FUNC(Camera::OnWindowResized, this));
	}

	void Camera::Resize(float width, float height)
	{
		m_SpeedMultiplier = 2.0f / height;
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

	bool Camera::OnWindowResized(WindowResizeEvent& event)
	{
		return false;
	}

	////////////////* Camera Implementations Lie Here *////////////////

	OrthographicCamera::OrthographicCamera(float aspectRatio)
		: Camera(aspectRatio)
	{
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);
	}
}


