#include <Physics/Collider.hpp>

namespace Physics
{
	Collider::Collider(ColliderType type, int* shader) :
		mModel(nullptr), Type(type), mShaderProgram(shader)
	{
	}

	void Collider::Draw(const Core::Maths::Mat4& mvp)
	{
		glBindVertexArray(mModel->mSubobjects[0].VAO);

		glUseProgram(*mShaderProgram);

		glUniformMatrix4fv(glGetUniformLocation(*mShaderProgram, "mvp"), 1, GL_TRUE, &mvp.mat[0][0]);
		glUniform1i(glGetUniformLocation(*mShaderProgram, "isColliding"), (int)mIsColliding);
		mIsColliding = false;

		glDrawElements(GL_LINE_LOOP, (GLsizei)mModel->mSubobjects[0].IndexBuffer.size(), GL_UNSIGNED_INT, 0);
	}

	BoxCollider::BoxCollider(int* shader) : Collider(ColliderType::COLT_BOX, shader)
	{
		Resources::Model* cube = Resources::ResourceManager::GetInstance()->Get<Resources::Model>("cube");
		if (!cube)
		{
			cube = Core::Maths::Primitive::Cube();
			Resources::ResourceManager::GetInstance()->Create<Resources::Model>("cube", cube);
		}
		SetModel(cube);
		mStartingData[0] = Vec3(-0.5f, -0.5f, -0.5f);
		mStartingData[1] = Vec3(-1.f, 0.f, 0.f);
		mStartingData[2] = Vec3(0.f, -1.f, 0.f);
		mStartingData[3] = Vec3(0.f, 0.f, -1.f);

		mStartingData[4] = Vec3(0.5f, 0.5f, 0.5f);
		mStartingData[5] = Vec3(1.f, 0.f, 0.f);
		mStartingData[6] = Vec3(0.f, 1.f, 0.f);
		mStartingData[7] = Vec3(0.f, 0.f, 1.f);
	}

	void BoxCollider::UpdateCollisionData(Mat4& model)
	{
		for (int i = 0; i < 8; ++i)
		{
			Vec4 tmp = model * Vec4(mStartingData[i], (i == 0 || i == 4) ? 1.f : 0.f);
			CollisionData[i] = Vec3(tmp.x, tmp.y, tmp.z);
			if (i != 0 && i != 4)
				CollisionData[i] = CollisionData[i].Normalize();
		}

	}

	void BoxCollider::ComputeBoundaries(const Transform& transform)
	{
		Boundaries.min = transform.Position - transform.Scale / 2.f;
		Boundaries.max = transform.Position + transform.Scale / 2.f;
	}

	void BoxCollider::ComputeCollision(Collider* other, const Vec3& otherScale, Vec3* position)
	{
		if (other->Type != ColliderType::COLT_BOX)
			return;
		BoxCollider* col = reinterpret_cast<BoxCollider*>(other);
		if ((Boundaries.min.x < col->Boundaries.max.x && Boundaries.max.x > col->Boundaries.min.x) &&
			(Boundaries.min.y < col->Boundaries.max.y && Boundaries.max.y > col->Boundaries.min.y) &&
			(Boundaries.min.z < col->Boundaries.max.z && Boundaries.max.z > col->Boundaries.min.z))
		{
			float Xx = fabsf(col->Boundaries.max.x - Boundaries.min.x);
			float xX = fabsf(col->Boundaries.min.x - Boundaries.max.x);
			float Yy = fabsf(col->Boundaries.max.y - Boundaries.min.y);
			float yY = fabsf(col->Boundaries.min.y - Boundaries.max.y);
			float Zz = fabsf(col->Boundaries.max.z - Boundaries.min.z);
			float zZ = fabsf(col->Boundaries.min.z - Boundaries.max.z);
			float minDist = fminf(fminf(fminf(fminf(fminf(Xx, xX), Yy), yY), Zz), zZ);

			if (minDist == Xx)
				position->x += col->Boundaries.max.x - Boundaries.min.x;
			else if (minDist == xX)
				position->x += col->Boundaries.min.x - Boundaries.max.x;
			else if (minDist == Yy)
				position->y += col->Boundaries.max.y - Boundaries.min.y;
			else if (minDist == yY)
				position->y += col->Boundaries.min.y - Boundaries.max.y;
			else if (minDist == Zz)
				position->z += col->Boundaries.max.z - Boundaries.min.z;
			else if (minDist == zZ)
				position->z += col->Boundaries.min.z - Boundaries.max.z;

			mIsColliding = true;
			col->SetColliding();
		}
	}

	SphereCollider::SphereCollider(int* shader) : Collider(ColliderType::COLT_SPHERE, shader)
	{
		Resources::Model* sphere = Resources::ResourceManager::GetInstance()->Get<Resources::Model>("sphere");
		if (!sphere)
		{
			sphere = Core::Maths::Primitive::Sphere(10);
			Resources::ResourceManager::GetInstance()->Create<Resources::Model>("sphere", sphere);
		}
		SetModel(sphere);
	}

	void SphereCollider::ComputeBoundaries(const Transform& transform)
	{
		Sphere.center = transform.Position;
		Sphere.radius = fmaxf(fmaxf(transform.Scale.x, transform.Scale.y), transform.Scale.z) * 0.5f;
	}

	void SphereCollider::SinglePlaneCheck(Vec3* position, const Vec3& planeOrig, const Vec3& planeNormal)
	{
		Vec3 v = Sphere.center - planeOrig;
		float scalarDistance = planeNormal.DotProduct(v);
		Vec3 pointOnPlane = Sphere.center - planeNormal * scalarDistance;

		if (planeNormal.DotProduct(Sphere.center - pointOnPlane) > 0.f)
		{
			float distanceCenterPlane = Sphere.radius - (Sphere.center - pointOnPlane).Magnitude();
			if (distanceCenterPlane > 0.f)
			{
				mIsColliding = true;
				*position += planeNormal * distanceCenterPlane;
			}
		}
	}

	void SphereCollider::ComputeCollision(Collider* other, const Vec3& otherScale, Vec3* position)
	{
		if (!other || other->Type != ColliderType::COLT_BOX)
			return;

		BoxCollider* col = reinterpret_cast<BoxCollider*>(other);

		Vec3 boxCenter = (col->CollisionData[0] + col->CollisionData[4]) * 0.5f;

		if (((Sphere.center - col->CollisionData[5] * Sphere.radius) - col->CollisionData[0]).DotProduct(col->CollisionData[5]) > otherScale.x ||
			((Sphere.center + col->CollisionData[5] * Sphere.radius) - col->CollisionData[0]).DotProduct(col->CollisionData[5]) < 0.f ||
			((Sphere.center - col->CollisionData[6] * Sphere.radius) - col->CollisionData[0]).DotProduct(col->CollisionData[6]) > otherScale.y ||
			((Sphere.center + col->CollisionData[6] * Sphere.radius) - col->CollisionData[0]).DotProduct(col->CollisionData[6]) < 0.f ||
			((Sphere.center - col->CollisionData[7] * Sphere.radius) - col->CollisionData[0]).DotProduct(col->CollisionData[7]) > otherScale.z ||
			((Sphere.center + col->CollisionData[7] * Sphere.radius) - col->CollisionData[0]).DotProduct(col->CollisionData[7]) < 0.f)
			return;
		
		SinglePlaneCheck(position, col->CollisionData[0], col->CollisionData[1]);
		SinglePlaneCheck(position, col->CollisionData[0], col->CollisionData[2]);
		SinglePlaneCheck(position, col->CollisionData[0], col->CollisionData[3]);
		SinglePlaneCheck(position, col->CollisionData[4], col->CollisionData[5]);
		SinglePlaneCheck(position, col->CollisionData[4], col->CollisionData[6]);
		SinglePlaneCheck(position, col->CollisionData[4], col->CollisionData[7]);
	}

	CapsuleCollider::CapsuleCollider(int* shader) : Collider(ColliderType::COLT_CAPSULE, shader)
	{
		Resources::Model* capsule = Resources::ResourceManager::GetInstance()->Get<Resources::Model>("capsule");
		if (!capsule)
		{
			capsule = Core::Maths::Primitive::Capsule(10);
			Resources::ResourceManager::GetInstance()->Create<Resources::Model>("capsule", capsule);
		}
		SetModel(capsule);
	}

	void CapsuleCollider::ComputeBoundaries(const Transform& transform)
	{

	}

	void CapsuleCollider::ComputeCollision(Collider* other, const Vec3& otherScale, Vec3* position)
	{
	}
}