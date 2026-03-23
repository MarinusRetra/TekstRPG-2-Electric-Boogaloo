#ifndef GAMEUTILITY_H
#define GAMEUTILITY_H

#include "REXSpeeder.h"

namespace game_utility
{
	uint32_t ConvertTileToTileIndex(xp::RexTile tile);

	//I use this instead of y * width + x. This optimization is not necessary but it was fun to add.
	// High 8 bits = y, low 8 bits = x.
	static uint16_t EncodePos(uint8_t x, uint8_t y) { return (y << 8) | x; }
	static uint8_t DecodePosX(uint16_t _posIn) { return _posIn & 0xFF; }
	static uint8_t DecodePosY(uint16_t _posIn) { return _posIn >> 8; }
	template<typename T = uint8_t>
	struct Vector2
	{
		T X;
		T Y;

		Vector2(T x, T y)
		{
			X = x;
			Y = y;
		}
		Vector2()
		{
			X = 0;
			Y = 0;
		}

		uint16_t GetPos() const
		{
			return (EncodePos(X, Y));
		}

		// Is used to update the vector2's x and y based of a position.
		Vector2& SetVectorFromPos(uint16_t _posIn)
		{
			X = DecodePosX(_posIn);
			Y = DecodePosY(_posIn);
			return *this;
		}

		Vector2 operator+(const Vector2& other) const
		{
			Vector2 result = *this;
			result.X += other.X;
			result.Y += other.Y;
			return result;
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

		// Gets a vector with x and y set based of the position provided. Probably won't get used much. 
		static Vector2 GetVectorFromPos(uint16_t _posIn)
		{
			return Vector2{ DecodePosX(_posIn), DecodePosY(_posIn) };
		}

		// Gets a packed position from a vector. Also probaly won't get used much.
		static uint16_t GetPosFromVector(Vector2 vec)
		{
			return (EncodePos(vec.X, vec.Y));
		}
	};
}


#endif 
