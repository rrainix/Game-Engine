#pragma once
#include "Vec2.hpp"
#include "Mat2.hpp"

namespace Engine {
	struct AABB {
		Vec2 Min;
		Vec2 Max;

		AABB() = default;
		AABB(Vec2 min, Vec2 max) : Min(min), Max(max) {}

		static AABB Create(const Vec2& center, const Vec2& halfExtents, float degrees)
		{
			float radians = Engine::Radians<float>(degrees);
			Mat2 rotation = Engine::Rotation(radians);


			Vec2 corners[4] = {
				Vec2(-halfExtents.x, -halfExtents.y),
				Vec2(halfExtents.x, -halfExtents.y),
				Vec2(halfExtents.x, halfExtents.y),
				Vec2(-halfExtents.x, halfExtents.y)
			};


			Vec2 rotatedCorners[4];
			for (int i = 0; i < 4; ++i) {
				rotatedCorners[i] = center + rotation * corners[i];
			}


			Vec2 minVec = rotatedCorners[0];
			Vec2 maxVec = rotatedCorners[0];
			for (int i = 1; i < 4; ++i) {
				minVec.x = std::min(minVec.x, rotatedCorners[i].x);
				minVec.y = std::min(minVec.y, rotatedCorners[i].y);
				maxVec.x = std::max(maxVec.x, rotatedCorners[i].x);
				maxVec.y = std::max(maxVec.y, rotatedCorners[i].y);
			}

			return { minVec, maxVec };
		}

		static AABB Create(const Vec2& center, const Vec2& halfExtents)
		{
			Vec2 minVec = center - halfExtents;
			Vec2 maxVec = center + halfExtents;
			return { minVec, maxVec };
		}

		static AABB FromTransform(const Transform2D& transform) {
			if (IsAxisAligned(transform.Rotation)) {
				return AABB::Create(
					Vec2(transform.Position.x, transform.Position.y),
					Vec2(transform.Scale.x * 0.5f, transform.Scale.y * 0.5f)
				);
			}
			else {
				return AABB::Create(
					transform.Position,
					transform.Scale * 0.5f,
					transform.GetRotationDegrees()
				);
			}
		}

		static bool Intersects(const AABB& a, const AABB& b) {
			return (a.Min.x <= b.Max.x && a.Max.x >= b.Min.x) &&
				(a.Min.y <= b.Max.y && a.Max.y >= b.Min.y);
		}

		static bool Contains(const AABB& a, const Vec2& point) {
			return (point.x >= a.Min.x && point.x <= a.Max.x) &&
				(point.y >= a.Min.y && point.y <= a.Max.y);
		}

		Vec2 Scale() const {
			float x = Max.x - Min.x;
			float y = Max.y - Min.y;
			return { x, y };
		}

		static bool IsAxisAligned(float radians) {
			constexpr float tolerance = 1e-6f;

			const float angles[] = {
				0.0f,
				Engine::HalfPi<float>(),
				Engine::Pi<float>(),
				3 * Engine::HalfPi<float>(),
				Engine::TwoPi<float>()
			};


			float normalizedRadians = std::fmod(radians, Engine::TwoPi<float>());
			if (normalizedRadians < 0) {
				normalizedRadians += Engine::TwoPi<float>();
			}

			for (float angle : angles) {
				if (std::abs(normalizedRadians - angle) < tolerance) {
					return true;
				}
			}
			return false;
		}
	};
}