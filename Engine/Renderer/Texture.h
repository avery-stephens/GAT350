#pragma once
#include "Math/Vector2.h"
#include "Resource/Resource.h"
#include "Renderer.h"
#include <string>

struct SDL_Texture;
struct SDL_Surface;
// !! forward declaration for SDL pointers below (SDL likes to use structs)

namespace boogleborg
{
	// !! forward declaration for Renderer below
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string filename, ...) override;
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		bool Load(const std::string& filename, Renderer& renderer);

		void SetActive(GLuint unit) { glActiveTexture(unit); }
		void Bind() { glBindTexture(m_target, m_texture); }

		Vector2 GetSize() const;

		friend class Renderer;

	private:
		void FlipSurface(SDL_Surface* surface);

		GLuint m_texture;
		GLenum m_target = GL_TEXTURE_2D;
	};
}
