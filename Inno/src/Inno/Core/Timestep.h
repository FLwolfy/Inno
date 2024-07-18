#pragma once

namespace Inno {

	class Timestep
	{
		friend class Application;
	public:
		/**
		 * @brief Gets the delta time between every two frame (in seconds).
		 */
		static inline const float GetDeltaTimeSeconds() { return m_Time; }
		/**
		 * @brief Gets the delta time between every two frame (in milliseconds).
		 */
		static inline const float GetDeltaTimeMilliseconds() { return m_Time * 1000.0f; }
	private:
		static float m_Time;
	};

}
