#pragma once

namespace ECS
{
	//#PURE_ENTITY
	struct PureEntity
	{
	public:
		PureEntity()
		{
			_uID = nextID++;
		}

		unsigned int const getUID() const
		{
			return _uID;
		}

	private:
		unsigned int _uID;
		static unsigned int nextID;

	public:
		// Operator overload
		bool operator==(const PureEntity& other)
		{
			return this->_uID == other.getUID();
		}

		bool operator!=(const PureEntity& other)
		{
			return !(this->_uID == other.getUID());
		}
	};
}