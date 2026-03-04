#ifndef GAMEUTILITY_H
#define GAMEUTILITY_H

#include "REXSpeeder.h"

namespace game_utility
{
	uint32_t ConvertTileToUint32(xp::RexTile tile);

	template<typename TypeOfNumber>
	struct Vector2
	{
		TypeOfNumber X;
		TypeOfNumber Y;

		Vector2 operator+(const Vector2& other) const
		{
			return Vector2{ X + other.X, Y + other.Y };
		}

		Vector2& operator+=(const Vector2& other) {
			X += other.X;
			Y += other.Y;
			return *this;
		}

		bool operator==(const Vector2& other) const
		{
			return X == other.X && Y == other.Y;
		}

		bool operator<(const Vector2& other) const
		{
			if (X != other.X)
				return X < other.X;
			return Y < other.Y;
		}

		bool operator>(const Vector2& other) const
		{
			if (X != other.X)
				return X > other.X;
			return Y > other.Y;
		}

		bool operator!=(const Vector2& other) const
		{
			return X != other.X || Y != other.Y;
		}

		bool IsInBounds(Vector2 minBound, Vector2 maxBound) const
		{
			return X >= minBound.X && X <= maxBound.X && Y >= minBound.Y && Y <= maxBound.Y;
		}

	};

}


#endif 
