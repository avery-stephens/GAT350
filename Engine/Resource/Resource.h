#pragma once
#include <string>

namespace boogleborg
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;
	};
}
