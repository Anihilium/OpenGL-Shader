#pragma once
#include <iostream>
#include <vector>
#include <Resources/Model.hpp>
#include <Maths/Vec3.hpp>
#include <Maths/Mat4.hpp>

namespace Core::Maths
{
	class Primitive
	{
	public:
		static Resources::Model* Cube();
		static Resources::Model* Sphere(const int subDiv);
		static Resources::Model* Cylinder(const int sectorAmount);
		static Resources::Model* Capsule(const int sectorAmount);
		static void ComputeTangents(std::vector<Resources::Vertex>& vertices);
	};

}