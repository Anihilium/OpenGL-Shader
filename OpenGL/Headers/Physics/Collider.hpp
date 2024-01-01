#pragma once

#include <Resources/ResourceManager.hpp>
#include <Resources/Model.hpp>
#include <Resources/Shader.hpp>
#include <Maths/Vec4.hpp>
#include <Maths/Mat4.hpp>
#include <Maths/Primitive.hpp>
#include <Physics/Transform.hpp>

namespace Physics
{
	enum class ColliderType
	{
		COLT_NONE,
		COLT_BOX,
		COLT_SPHERE,
		COLT_CAPSULE
	};

	class Collider
	{
	public:
		ColliderType Type;

	protected:
		int* mShaderProgram;
		Resources::Model* mModel;
		bool mIsColliding;

	public:
		Collider(ColliderType type, int* shader);
		virtual void ComputeBoundaries(const Transform& transform) = 0;
		virtual void ComputeCollision(Collider* other, const Vec3& otherScale, Vec3* position) = 0;
		void Draw(const Core::Maths::Mat4& mvp);
		void SetColliding() { mIsColliding = true; };
		bool IsColliding() { return mIsColliding; };

	protected:
		void SetModel(Resources::Model* model) { mModel = model; };
	};

	class BoxCollider : public Collider
	{
	public:
		struct
		{
			Vec3 min;
			Vec3 max;
		} Boundaries;
		Vec3 CollisionData[8]; // point1; normal1; normal2; normal3; point2; normal4; normal5; normal6

	private:
		Vec3 mStartingData[8];

	public:
		BoxCollider(int* shader);
		void ComputeBoundaries(const Transform& transform) override;
		void ComputeCollision(Collider* other, const Vec3& otherScale, Vec3* position) override;
		void UpdateCollisionData(Mat4& model);
	};

	class SphereCollider : public Collider
	{
	public:
		struct
		{
			Vec3 center;
			float radius;
		} Sphere;

	public:
		SphereCollider(int* shader);
		void ComputeBoundaries(const Transform& transform) override;
		void ComputeCollision(Collider* other, const Vec3& otherScale, Vec3* position) override;

	private:
		void SinglePlaneCheck(Vec3* position, const Vec3& planeOrig, const Vec3& planeNormal);
	};

	class CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(int* shader);
		void ComputeBoundaries(const Transform& transform) override;
		void ComputeCollision(Collider* other, const Vec3& otherScale, Vec3* position) override;
	};
}