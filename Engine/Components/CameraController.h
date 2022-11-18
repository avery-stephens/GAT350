#pragma once
#include "Framework/Component.h" 

namespace boogleborg
{
	class Program;
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

		void Initialize() override;
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float sensitivity = 0.1f;
		float speed = 0;
	private:
		float m_yaw = 0; // left/right
		float m_pitch = 0;// up / down
	};
}