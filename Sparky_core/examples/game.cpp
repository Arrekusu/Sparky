#include "../src/sparky.h"

using namespace sparky;
using namespace graphics;

class Game : public Sparky
{
private:
	Window* window;
	Layer* layer;
	Label* fps;
	Sprite* sprite;
	Shader* shader;
public:
	Game()
	{

	}

	~Game()
	{
		delete layer;
	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		shader = new Shader("src/shader/basic.vert", "src/shader/basic.frag");
		layer = new Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		sprite = new Sprite(0.0f, 0.0f, 5, 5, new Texture("test1.png"));
		layer->add(sprite);

		fps = new Label("", -15.5f, 7.8f, 0xffffffff);
		layer->add(fps);
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS());
	}

	void update() override
	{
		float speed = 0.5f;
		if (window->isKeyPressed(GLFW_KEY_UP))
			sprite->position.y += speed;
		if (window->isKeyPressed(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			sprite->position.x -= speed;
		if (window->isKeyPressed(GLFW_KEY_RIGHT))
			sprite->position.x += speed;

		double x, y;
		window->getMousePosition(x, y);

		shader->setUniform2f("light_pos", maths::vec2((float)(x * 32.0 / window->getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->getHeight())));


	}

	void render() override
	{
		layer->render();
	}
};

int main()
{
	Game game;
	game.start();

	return 0;
}