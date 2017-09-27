#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/Simple2dRenderer.h"
#include "src/graphics/BatchRenderer2D.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/utils/timer.h"
#include "src/graphics/layers/tile_layer.h"
#include "src/graphics/layers/group.h"

#include <time.h>

#define TEST_50K_SPRITES 0

int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!!", 800, 600);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	Shader* s1 = new Shader("src/shader/basic.vert", "src/shader/basic.frag");
	Shader* s2 = new Shader("src/shader/basic.vert", "src/shader/basic.frag");

	TileLayer layer1(s1);

#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer1.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else
	Group* group = new Group(mat4::translation(maths::vec3(-15.0f, 5.0f, 0.0f)));
	group->add(new Sprite(0, 0, 6, 3, maths::vec4(1, 1, 1, 1)));

	Group* button = new Group(mat4::translation(vec3(0.5f, 0.5f, 0.0f)));
	button->add(new Sprite(0, 0, 5, 2, maths::vec4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, maths::vec4(0.2f, 0.3f, 0.8f, 1)));
	group->add(button);

	layer1.add(group);
	
#endif

	TileLayer layer2(s2);
	layer2.add(new Sprite(-2, -2, 5, 5, maths::vec4(1, 0, 1, 1)));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		
		s1->enable();
		//s1->setUniform2f("light_pos", vec2(3, 2));
		s1->setUniform2f("light_pos", vec2((float)(x * 32.0 / 800.0f - 16.0f), (float)(9.0f - y * 18.0f / 600.0f)));
		s2->enable();
		s2->setUniform2f("light_pos", vec2((float)(x * 32.0 / 800.0f - 16.0f), (float)(9.0f - y * 18.0f / 600.0f)));

		layer1.render();
		//layer2.render();

		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
	
	return 0;
}