#pragma once

#include "graphics/label.h"
#include "graphics/font_manager.h"
#include "graphics/sprite.h"
#include "graphics/Renderer2D.h"
#include "graphics/BatchRenderer2D.h" 
#include "graphics/window.h"
#include "graphics/layers/layer.h"

#include "maths/maths.h"
#include "utils/timer.h"

namespace sparky {

	class Sparky
	{
	private:
		graphics::Window* m_Window;
		Timer* m_Timer;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
	public:
		void start()
		{
			init();
			run();
		}
	protected:
		Sparky()
			:m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}
		virtual ~Sparky()
		{
			delete m_Timer;
			delete m_Window;
		}

		graphics::Window* createWindow(const char *name, int width, int height)
		{
			m_Window = new graphics::Window(name, width, height);
			return m_Window;
		}

		//Once on itit
		virtual void init() = 0;
		// Once per sec
		virtual void tick() {};
		// 60 times per sec
		virtual void update() {};
		// As fast as possible (depending on vSync)
		virtual void render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }
	private:
		void run()
		{
			m_Timer = new Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;
			while (!m_Window->closed())
			{
				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					updates++;
					update();
					updateTimer += updateTick;
				}
				render();
				frames++;
				m_Window->update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
			}
		}
	};
}