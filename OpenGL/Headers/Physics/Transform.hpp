#pragma once
#include <Maths/Vec3.hpp>

using namespace Core::Maths;

namespace Physics
{
	class Transform
	{
	public:
		Vec3 Position;
		Vec3 Scale;
		Vec3 Rotation;

	public:
		Transform(const Vec3& pos = Vec3(0.f, 0.f, 0.f), const Vec3& scale = Vec3(1.f, 1.f, 1.f), const Vec3& rot = Vec3(0.f, 0.f, 0.f));
	};
}