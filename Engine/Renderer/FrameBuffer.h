#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"

namespace boogleborg
{
	class Texture;

	class FrameBuffer : public Resource
	{
	public:
		~FrameBuffer();

		bool Create(std::string filename, ...) override;
		bool CreateFramebuffer();
		bool CreateDepthbuffer(int width, int height);
		glm::ivec2 GetSize() const { return { m_width, m_height }; }

		void Bind();
		void Unbind();

	private:
		int m_width = 0;
		int m_height = 0;
	protected:
		GLuint m_fbo = 0;
		std::shared_ptr<Texture> m_texture;
	};
}