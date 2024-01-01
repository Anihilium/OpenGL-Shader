#pragma once
#include <Maths/Vec3.hpp>
#include <Maths/Vec4.hpp>

using namespace Core::Maths;

namespace LowRenderer
{
	class Light
	{
	public:
		Vec4 AmbientColor;
		Vec4 DiffuseColor;
		Vec4 SpecularColor;

	public:
		Light(const Vec4& ambient, const Vec4& diffuse, const Vec4& specular);
	};

	class DirectionalLight : public Light
	{
	public:
		Vec3 Direction;

	public:
		DirectionalLight(
			const Vec3& direction = Vec3(0.f, 0.f, 0.f),
			const Vec4& ambient = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec4& diffuse = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec4& specular = Vec4(1.f, 1.f, 1.f, 1.f)
		);
	};

	class PointLight : public Light
	{
	public:
		Vec3 Position;
		Vec3 AttenuationValues; // Constant, Linear, Quadratic

	public:
		PointLight(
			const Vec3& position = Vec3(0.f, 0.f, 0.f),
			const Vec4& ambient = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec4& diffuse = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec4& specular = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec3& attenuationValues = Vec3(1.f, 0.09f, 0.032f)
		);
	};

	class SpotLight : public Light
	{
	public:
		Vec3 Position;
		Vec3 Direction;
		Vec3 AttenuationValues; // Constant, Linear, Quadratic
		float InnerCutOff; // Put the cosine of the desired angle
		float OuterCutOff; // Same

	public:
		SpotLight(
			const Vec3& position = Vec3(0.f, 0.f, 0.f),
			const Vec3& direction = Vec3(0.f, 0.f, 0.f),
			const float innerCutOff = 0.f,
			const float outerCutOff = 0.f,
			const Vec4& ambient = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec4& diffuse = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec4& specular = Vec4(1.f, 1.f, 1.f, 1.f),
			const Vec3& attenuationValues = Vec3(1.f, 0.09f, 0.032f)
		);
	};
}