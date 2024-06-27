#pragma once

#include "Inno/Events/Event.h"

namespace Inno
{
	class Layer
	{
	public:
		/// <summary>
		/// Constructs a Layer with the given name.
		/// </summary>
		/// <param name="name">The name of the layer. Default is "Layer".</param>
		Layer(const std::string& name = "Layer")
			: m_Name(name) {}
		virtual ~Layer() = default;

		/// <summary>
		/// Called when the layer is attached.
		/// </summary>
		virtual void OnAttach() {}

		/// <summary>
		/// Called when the layer is detached.
		/// </summary>
		virtual void OnDetach() {}

		/// <summary>
		/// Called every frame to update the layer.
		/// </summary>
		virtual void OnUpdate() {}

		/// <summary>
		/// Called when an event occurs.
		/// </summary>
		/// <param name="event">The event that occurred.</param>
		virtual void OnEvent(Event& event) {}

		/// <summary>
		/// Returns the name of the layer.
		/// </summary>
		/// <returns>The name of the layer.</returns>
		const std::string& GetName() const { return m_Name; }

		operator std::string() const
		{
			return GetName();
		}
	protected:
		/// <summary>
		/// The name of the layer.
		/// </summary>
		std::string m_Name;
	};
}
