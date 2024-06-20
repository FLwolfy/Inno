#pragma once

#include "Inno/Events/Event.h"

namespace Inno
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			: m_Name(name) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_Name; }

		operator std::string() const
		{
			return GetName();
		}
	protected:
		std::string m_Name;
	};
}
