#pragma once

namespace ECS
{
	enum class ComponentType
	{
		// PHYSICS
		POSITION = 0x0,
		VELOCITY,

		// COMBAT
		HEALTH,

		NUM_COMPONENT_TYPES
	};

	class PureComponent
	{
	public:

	};
}