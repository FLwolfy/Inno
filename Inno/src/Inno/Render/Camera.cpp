#include "pch.h"
#include "Camera.h"

#include "Inno/Render/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Inno
{
	////////////////* Camera Interface Lies Here *////////////////

	Camera::Camera()
		: m_ViewMatrix(1.0f)
	{
		SetViewProjectionMatrix();
	}

    void Camera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

        /* Apply rotations in the order Z, Y, X */
        transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));
        transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));

        m_ViewMatrix = glm::inverse(transform);
		SetViewProjectionMatrix();
    }

	void Camera::SetViewProjectionMatrix()
	{
        switch (Renderer::Command::GetAPI())
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

	////////////////* Camera Implementations Lie Here *////////////////

	OrthographicCamera::OrthographicCamera(float leftB, float rightB, float bottomB, float topB)
		: Camera()
	{
		m_ProjectionMatrix = glm::ortho(leftB, rightB, bottomB, topB, -1.0f, 1.0f);
	}
}


