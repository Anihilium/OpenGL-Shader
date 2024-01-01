#include <LowRenderer/Light.hpp>

namespace LowRenderer
{
	Light::Light(const Vec4& ambient, const Vec4& diffuse, const Vec4& specular):
		AmbientColor(ambient),
		DiffuseColor(diffuse),
		SpecularColor(specular)
	{}

	DirectionalLight::DirectionalLight(const Vec3& direction, const Vec4& ambient, const Vec4& diffuse, const Vec4& specular) :
		Light(ambient, diffuse, specular),
		Direction(direction)
	{}

	PointLight::PointLight(const Vec3& position, const Vec4& ambient, const Vec4& diffuse, const Vec4& specular, const Vec3& attenuationValues) :
		Light(ambient, diffuse, specular),
		Position(position),
		AttenuationValues(attenuationValues)
	{}

	SpotLight::SpotLight(const Vec3& position, const Vec3& direction, const float innerCutOff, const float outerCutOff, const Vec4& ambient, const Vec4& diffuse, const Vec4& specular, const Vec3& attenuationValues):
		Light(ambient, diffuse, specular),
		Position(position),
		Direction(direction),
		InnerCutOff(innerCutOff),
		OuterCutOff(outerCutOff),
		AttenuationValues(attenuationValues)
	{}
}