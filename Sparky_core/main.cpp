#if 0
#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/BatchRenderer2D.h"
#include "src/graphics/sprite.h"
#include "tile_layer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/label.h"
#include "src/graphics/font_manager.h"
#include "src/audio/sound_manager.h"
#include <FreeImage.h>

#if 1
int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace maths;
	using namespace audio;

	Window window("Sparky!!", 800, 600);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Shader* s1 = new Shader("src/shader/basic.vert", "src/shader/basic.frag");
	
	TileLayer layer1(s1);

	Texture* textures[] =
	{
		new Texture("test1.png"),
		new Texture("test2.png"),
		new Texture("test3.png")
	};
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			int r = rand() % 256;
			int col = 0xffff00 << 8 | r;
			if (rand() % 4 == 0) 
				layer1.add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
				layer1.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.0f, 7.0f, 0.0f)));
	Label* fps = new Label("fps", 0.4f, 0.4f, 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050dd));
	g->add(fps);
	layer1.add(g);

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	s1->enable();
	s1->setUniform1iv("textures", texIDs, 10);
	s1->setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	SoundManager::add(new Sound("Test", "Test.wav"));
	SoundManager::get("Test")->play();

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float t = 0.0f;
	float gain = 0.5f;
	SoundManager::get("Test")->setGain(gain);
	while (!window.closed())
	{
		t += 0.01f;
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		
		s1->setUniform2f("light_pos", vec2((float)(x * 32.0 / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		
		layer1.render();
		
		const std::vector<Renderable2D*>& rs = layer1.getRenderables();
		for (int i = 0; i < rs.size(); i++)
		{
			float c = sin(t) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(c, 0, 1, 1));
		}
		
		if (window.isKeyTyped(GLFW_KEY_P)) 
			SoundManager::get("Test")->play();

		if (window.isKeyTyped(GLFW_KEY_1))
			SoundManager::get("Test")->pause();

		if (window.isKeyTyped(GLFW_KEY_2))
			SoundManager::get("Test")->resume();

		if (window.isKeyTyped(GLFW_KEY_L))
			SoundManager::get("Test")->loop();

		if (window.isKeyTyped(GLFW_KEY_S))
			SoundManager::get("Test")->stop();

		if (window.isKeyTyped(GLFW_KEY_UP))
		{
			gain += 0.05f;
			SoundManager::get("Test")->setGain(gain);
		}

		if (window.isKeyTyped(GLFW_KEY_DOWN))
		{
			gain -= 0.05f;
			SoundManager::get("Test")->setGain(gain);
		}
				
		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			frames = 0;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		delete textures[i];
	}

	return 0;
}
#endif
#endif
