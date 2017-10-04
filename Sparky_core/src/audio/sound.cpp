#include "sound.h"
#include "sound_manager.h"
#include <iostream>

#define GAU_THREAD_POLICY_MULTI 2

namespace sparky { namespace audio {
		
	Sound::Sound(const std::string & name, const std::string & filename)
		:m_Name(name), m_Filename(filename)
	{
		m_Sound = gau_load_sound_file(filename.c_str(), "wav");
	}

	Sound::~Sound()
	{
		ga_sound_release(m_Sound);
	}

	void Sound::play()
	{
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, NULL);
		ga_handle_play(m_Handle);
	}

	void Sound::loop()
	{
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &loopOnFinish, &quit, NULL);
		m_Handle->sound = this;
		ga_handle_play(m_Handle);
	}

	void Sound::pause()
	{
	}

	void Sound::stop()
	{
		ga_handle_stop(m_Handle);
	}

	void Sound::setGain(float gain)
	{
		if (!ga_handle_playing(m_Handle))
		{
			std::cout << "Cannot set gain! No sound is playing!" << std::endl;
			return;
		}
		m_Gain = gain;
		ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
	}

	void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		Sound* sound = (Sound*)in_handle->sound;
		gc_int32* flag = (gc_int32*)(in_context);
		*flag = 1;
		ga_handle_destroy(in_handle);		
	}

	void loopOnFinish(ga_Handle* in_handle, void * in_context)
	{
		Sound* sound = (Sound*)in_handle->sound;
		sound->loop();
		ga_handle_destroy(in_handle);
	}
} }
