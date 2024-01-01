#include <Physics/Transform.hpp>

namespace Physics
{
	Transform::Transform(const Vec3& pos, const Vec3& scale, const Vec3& rot):
		Position(pos),
		Scale(scale),
		Rotation(rot)
	{}
}