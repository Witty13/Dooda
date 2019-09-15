#pragma once

namespace Dooda {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: d_time(time)
		{
		}

		operator float() const { return d_time; }

		float GetSeconds() const { return d_time; }
		float GetMilliseconds() const { return d_time * 1000.0f; }
	private:
		float d_time;
	};

}