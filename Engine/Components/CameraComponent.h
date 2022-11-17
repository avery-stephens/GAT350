#pragma once 
#include "Framework/Component.h" 
#include "Renderer/Program.h"

namespace boogleborg
{
	class Program;
	class CameraComponent : public Component
	{
	public:
		CLASS_DECLARATION(CameraComponent)

		void Update() override;

		void SetPerspective(float fov, float aspectRatio, float near, float far);

		const glm::mat4& GetProjection() { return m_projection; }
		const glm::mat4& GetView() { return m_view; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void SetProgram(std::shared_ptr<Program> program);

	public:
		glm::mat4 m_projection{ 1 };
		glm::mat4 m_view{ 1 };
	};
}