#pragma once

namespace Inno {

	/// <summary>
	/// Abstract base class representing a graphics context.
	/// Provides an interface for initializing and managing the rendering context.
	/// </summary>
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		/// <summary>
		/// Initializes the graphics context.
		/// </summary>
		virtual void Init() = 0;
		/// <summary>
		/// Swaps the front and back render buffers.
		/// </summary>
		virtual void SwapBuffers() = 0;
	};
}
