#include "tile_layer.h"

namespace sparky {	namespace graphics {

	TileLayer::TileLayer(Shader * shader)
		: Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1, 1))
	{
	}
	TileLayer::~TileLayer()
	{
	}

}  }
