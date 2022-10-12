#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"

namespace boogleborg
{
	class Shader : public Resource
	{
	public:
		~Shader();

		virtual bool Create(std::string filename, ...) override;

		GLuint m_shader = 0;
	};
}