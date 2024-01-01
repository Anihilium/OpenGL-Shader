#include <LowRenderer/Camera.hpp>

namespace LowRenderer
{
    Camera::Camera(const Vec3& position, const Vec3& up, const float yaw, const float pitch, const int height, const int width) : Position(position), mUp(up), mYaw(yaw), mPitch(pitch), Aspect((float)width / (float)height), Front(Vec3(0.f, 0.f, -1.f)), mWorldUp(up)
    {
        UpdateVectors();
    }

    void Camera::UpdateVectors()
    {
        Vec3 front;
        front.x = cos(M_PI / 180.f * mYaw) * cos(M_PI / 180.f * mPitch);
        front.y = sin(M_PI / 180.f * mPitch);
        front.z = sin(M_PI / 180.f * mYaw) * cos(M_PI / 180.f * mPitch);
        Front = front.Normalize();
        // also re-calculate the Right and Up vector
        Right = Front.CrossProduct(mWorldUp).Normalize();
        mUp = Right.CrossProduct(Front).Normalize();
    }

    void Camera::Update(const float deltaTime, const Vec3& playerPos)
	{        
        Position = playerPos;
        CamInputs.deltaX *= mSensitivity;
        CamInputs.deltaY *= mSensitivity;

        mYaw += CamInputs.deltaX;
        mPitch += CamInputs.deltaY;

        if (mPitch < 0.1f)
            mPitch = 0.1f;
        if (mPitch > 89.9f)
            mPitch = 89.9f;

        UpdateVectors();

        ViewProjectionMatrix = GetProjectionMatrix() * GetViewMatrix(playerPos);
	}

    Mat4 Camera::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
    {
        Vec3 f = (center - eye).Normalize();
        Vec3 s = f.CrossProduct(up).Normalize();
        Vec3 u = s.CrossProduct(f);

        Mat4 Result = Mat4::Identity();
        Result.mat[0][0] = s.x;
        Result.mat[1][0] = s.y;
        Result.mat[2][0] = s.z;
        Result.mat[0][1] = u.x;
        Result.mat[1][1] = u.y;
        Result.mat[2][1] = u.z;
        Result.mat[0][2] = -f.x;
        Result.mat[1][2] = -f.y;
        Result.mat[2][2] = -f.z;
        Result.mat[3][0] = -s.DotProduct(eye);
        Result.mat[3][1] = -u.DotProduct(eye);
        Result.mat[3][2] = f.DotProduct(eye);

        Result = Result.Transpose();
        return Result;
    }

    Mat4 Camera::GetViewMatrix()
    {
        return LookAt(Position, Position + Front, mUp);
    }

    Mat4 Camera::GetViewMatrix(const Vec3& playerPos)
    {
        return LookAt(
            playerPos,
            -Vec3(
                cosf(M_PI / 180.f * mYaw) * sinf(M_PI / 180.f * mPitch),
                cosf(M_PI / 180.f * mPitch),
                sinf(M_PI / 180.f * mYaw) * sinf(M_PI / 180.f * mPitch)
            ) * 3.f + playerPos,
            mUp
        );
    }

    Mat4 Camera::GetProjectionMatrix()
    {
        float a = 1.f / tanf(M_PI / 180.f * mFOV / 2.f);
        Mat4 projection(
            a / Aspect, 0.f, 0.f, 0.f,
            0.f, a, 0.f, 0.f,
            0.f, 0.f, -(mFar + mNear) / (mFar - mNear), -(2 * mFar * mNear) / (mFar - mNear),
            0.f, 0.f, -1.f, 0.f
        );
        return projection;
    }
}