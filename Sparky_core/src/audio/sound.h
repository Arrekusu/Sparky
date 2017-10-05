#pragma once

#include <string>

#include "../../ext/gorilla-audio/gorilla/ga.h"
#include "../../ext/gorilla-audio/gorilla/gau.h"

namespace sparky { namespace audio {

	class Sound
	{
	private:
		std::string m_Name;
		std::string m_Filename;

		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		float m_Gain;
	public:
		Sound(const std::string& name, const std::string& filename);
		~Sound();
		void play();
		void loop();
		void pause();
		void resume();
		void stop();

		void setGain(float gain);

		inline float getGain() const { return m_Gain; };

		inline const std::string& getName() const {
			return m_Name;
		}

		inline const std::string& getFileName() const {
			return m_Filename;
		}

		friend void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
		friend void loopOnFinish(ga_Handle* in_handle, void* in_context);

	};
} }