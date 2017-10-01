#pragma once

#include "Renderable2d.h"

namespace sparky {	namespace graphics {
		
	class Label : public Renderable2D
	{
	public:
		std::string text;
		float x, y;
		maths::vec3& position;
	public:
		Label(std::string text, float x, float y, maths::vec4 color);
		void submit(Renderer2D* renderer) const override;
	};
} }
