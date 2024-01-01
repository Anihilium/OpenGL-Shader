#include <Maths/Primitive.hpp>

namespace Core::Maths
{
    void Primitive::ComputeTangents(std::vector<Resources::Vertex>& vertices)
    {
        const unsigned int vertexAmount = vertices.size();
        for (unsigned int i = 0; i < vertexAmount / 3; i += 3)
        {
            Vec3 tangent;
            Vec3 edge1 = vertices[i + 1].Position - vertices[i].Position;
            Vec3 edge2 = vertices[i + 2].Position - vertices[i].Position;
            Vec2 deltaUV1 = vertices[i + 1].TextureUV - vertices[i].TextureUV;
            Vec2 deltaUV2 = vertices[i + 2].TextureUV - vertices[i].TextureUV;

            float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

            tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
            tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
            tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

            tangent = tangent.Normalize();

            for (unsigned int j = 0; j < 3; ++j)
                vertices[i + j].Tangent = tangent;
        }
    }

    Resources::Model* Primitive::Cube()
    {
        std::vector<uint32_t> indexArray;
        std::vector<Resources::Vertex> vertices;

        vertices.push_back({ Vec3(-0.5f,-0.5f,-0.5f),       Vec3(0.0f,-1.0f, 0.0f),       Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f,-0.5f,-0.5f),     Vec3(0.0f,-1.0f, 0.0f),      Vec2(1.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f,-0.5f, 0.5f),     Vec3(0.0f,-1.0f, 0.0f),      Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());

        vertices.push_back({ Vec3(-0.5f,-0.5f, 0.5f),     Vec3(0.0f,-1.0f, 0.0f),      Vec2(0.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f,-0.5f,-0.5f),     Vec3(0.0f,-1.0f, 0.0f),      Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f,-0.5f, 0.5f),     Vec3(0.0f,-1.0f, 0.0f),      Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());

        vertices.push_back({ Vec3(-0.5f, 0.5f,-0.5f),     Vec3(-1.0f, 0.0f, 0.0f),     Vec2(0.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f,-0.5f,-0.5f),     Vec3(-1.0f, 0.0f, 0.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f, 0.5f, 0.5f),     Vec3(-1.0f, 0.0f, 0.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(-0.5f, 0.5f, 0.5f),     Vec3(-1.0f, 0.0f, 0.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f,-0.5f,-0.5f),     Vec3(-1.0f, 0.0f, 0.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f,-0.5f, 0.5f),     Vec3(-1.0f, 0.0f, 0.0f),     Vec2(1.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(-0.5f,-0.5f, 0.5f),     Vec3(0.0f, 0.0f, 1.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f, 0.5f),     Vec3(0.0f, 0.0f, 1.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f, 0.5f, 0.5f),     Vec3(0.0f, 0.0f, 1.0f),     Vec2(0.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(-0.5f,-0.5f, 0.5f),     Vec3(0.0f, 0.0f, 1.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f,-0.5f, 0.5f),     Vec3(0.0f, 0.0f, 1.0f),     Vec2(1.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f, 0.5f),     Vec3(0.0f, 0.0f, 1.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(0.5f, 0.5f,-0.5f),     Vec3(0.0f, 0.0f,-1.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f,-0.5f,-0.5f),     Vec3(0.0f, 0.0f,-1.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f, 0.5f,-0.5f),     Vec3(0.0f, 0.0f,-1.0f),     Vec2(0.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(-0.5f,-0.5f,-0.5f),     Vec3(0.0f, 0.0f,-1.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f,-0.5f),     Vec3(0.0f, 0.0f,-1.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f,-0.5f,-0.5f),     Vec3(0.0f, 0.0f,-1.0f),     Vec2(1.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(0.5f,-0.5f, 0.5f),     Vec3(1.0f, 0.0f, 0.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f,-0.5f,-0.5f),     Vec3(1.0f, 0.0f, 0.0f),     Vec2(1.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f,-0.5f),     Vec3(1.0f, 0.0f, 0.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(0.5f,-0.5f, 0.5f),     Vec3(1.0f, 0.0f, 0.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f,-0.5f),     Vec3(1.0f, 0.0f, 0.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f, 0.5f),     Vec3(1.0f, 0.0f, 0.0f),     Vec2(0.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(-0.5f, 0.5f, 0.5f),     Vec3(0.0f, 1.0f, 0.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f, 0.5f),     Vec3(0.0f, 1.0f, 0.0f),     Vec2(0.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f,-0.5f),     Vec3(0.0f, 1.0f, 0.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        
        vertices.push_back({ Vec3(-0.5f, 0.5f, 0.5f),     Vec3(0.0f, 1.0f, 0.0f),     Vec2(0.0f, 0.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(0.5f, 0.5f,-0.5f),     Vec3(0.0f, 1.0f, 0.0f),     Vec2(1.0f, 1.0f) });
        indexArray.push_back(indexArray.size());
        vertices.push_back({ Vec3(-0.5f, 0.5f,-0.5f),     Vec3(0.0f, 1.0f, 0.0f),     Vec2(1.0f, 0.0f) });
        indexArray.push_back(indexArray.size());

        ComputeTangents(vertices);

        Resources::Model* cube = new Resources::Model("");
        Resources::Subobject sub = Resources::Subobject();
        Resources::Subobject& ref = sub;
        ref.IndexBuffer = indexArray;
        ref.VertexBuffer = vertices;
        ref.SetBuffers();
        cube->mSubobjects.push_back(ref);
        return cube;
    }


    static Vec3 getSphericalCoords(float r, float theta, float phi)
    {
        return { r * sinf(theta) * cosf(phi),
                r * cosf(theta),
                r * sinf(theta) * sinf(phi) };
    }

    Resources::Model* Primitive::Sphere(const int subDiv)
    {
        float r = 0.5f;
        std::vector<uint32_t> indexArray;
        std::vector<Resources::Vertex> vertices;

        for (int j = 0; j <= subDiv; ++j)
        {
            float theta = (float)j / subDiv * M_PI;

            for (int i = 0; i <= subDiv; ++i)
            {
                float phi = (float)i / subDiv * 2.f * M_PI;

                Vec3 p = getSphericalCoords(r, theta, phi);

                vertices.push_back({ p, p, Vec2((float)i / subDiv, 1.f - (float)j / subDiv) });
            }
        }
        for (int i = 0; i < subDiv; ++i)
        {
            int k = i * (subDiv + 1);
            int l = k + subDiv + 1;
            for (int j = 0; j < subDiv; ++j)
            {
                if (i != 0) {

                indexArray.push_back(k);
                indexArray.push_back(k+1);
                indexArray.push_back(l);
                }

                if (i != (subDiv - 1))
                {
                indexArray.push_back(k+1);
                indexArray.push_back(l+1);
                indexArray.push_back(l);

                }

                ++k;
                ++l;
            }
        }

        ComputeTangents(vertices);

        Resources::Model* sphere = new Resources::Model("");
        Resources::Subobject sub = Resources::Subobject();
        Resources::Subobject& ref = sub;
        ref.IndexBuffer = indexArray;
        ref.VertexBuffer = vertices;
        ref.SetBuffers();
        sphere->mSubobjects.push_back(ref);
        return sphere;
	}

    Resources::Model* Primitive::Cylinder(const int sectorAmount)
    {
        Resources::Model* cylinder = new Resources::Model("");
        float height = 0.5f, radius = 0.5f;
        std::vector<uint32_t> indexArray;
        std::vector<Resources::Vertex> vertexArray;

        for (int i = 0; i < sectorAmount; ++i)
        {
            float curAngle = 2.f * M_PI * (float)i / (float)sectorAmount;

            Vec3 curVtxPos = Vec3(radius * cosf(curAngle), height, radius * sinf(curAngle));

            vertexArray.push_back(Resources::Vertex{ curVtxPos, curVtxPos, Vec2((float)i / sectorAmount, 1.f) });
            vertexArray.push_back(Resources::Vertex{ Vec3(curVtxPos.x, -curVtxPos.y, curVtxPos.z), Vec3(curVtxPos.x, -curVtxPos.y, curVtxPos.z), Vec2((float)i / sectorAmount, 0.f) });
        }
        vertexArray.push_back(vertexArray[0]);
        vertexArray[vertexArray.size() - 1].TextureUV.x = 1.0f;
        vertexArray.push_back(vertexArray[1]);
        vertexArray[vertexArray.size() - 1].TextureUV.x = 1.0f;

        for (int i = 0; i < sectorAmount; i++)
        {
            indexArray.push_back(i * 2);
            indexArray.push_back(i * 2 + 2);
            indexArray.push_back(i * 2 + 1);

            indexArray.push_back(i * 2 + 1);
            indexArray.push_back(i * 2 + 2);
            indexArray.push_back(i * 2 + 3);
        }


        vertexArray.push_back(Resources::Vertex{ Vec3(0.f, height, 0.f),  Vec3(0.f, 1.f, 0.f), Vec2(0.5f, 0.5f) });
        vertexArray.push_back(Resources::Vertex{ Vec3(0.f, -height, 0.f),  Vec3(0.f, -1.f, 0.f), Vec2(0.5f, 0.5f) });

        int size = vertexArray.size();
        
        for (int i = 0; i < sectorAmount; ++i)
        {
            float curAngle = 2.f * M_PI * (float)i / (float)sectorAmount;

            Vec3 curVtxPos = Vec3(radius * cosf(curAngle), height, radius * sinf(curAngle));

            vertexArray.push_back(Resources::Vertex{ curVtxPos, curVtxPos, Vec2(0.5f + cosf(curAngle) / 2.f, 0.5f + sinf(curAngle) / 2.f) });
            vertexArray.push_back(Resources::Vertex{ Vec3(curVtxPos.x, -curVtxPos.y, curVtxPos.z), Vec3(curVtxPos.x, -curVtxPos.y, curVtxPos.z), Vec2(0.5f + cosf(curAngle) / 2.f, 0.5f + sinf(curAngle) / 2.f) });
        }

        for (int i = 0; i < sectorAmount; i++)
        {
            indexArray.push_back(size + i * 2);
            indexArray.push_back(size - 2);
            indexArray.push_back(size + i * 2 + 2);

            indexArray.push_back(size - 1);
            indexArray.push_back(size + i * 2 + 1);
            indexArray.push_back(size + i * 2 + 3);
        }

        indexArray[indexArray.size() - 4] = indexArray[indexArray.size() / 2];
        indexArray[indexArray.size() - 1] = indexArray[indexArray.size() / 2 + 4];

        ComputeTangents(vertexArray);

        Resources::Subobject sub = Resources::Subobject();
        Resources::Subobject& ref = sub;
        ref.IndexBuffer = indexArray;
        ref.VertexBuffer = vertexArray;
        ref.SetBuffers();
        cylinder->mSubobjects.push_back(ref);
        return cylinder;
    }

    Resources::Model* Primitive::Capsule(const int sectorAmount)
    {
        float height = 0.5f, radius = 0.5f;

        std::vector<uint32_t> indexArray;
        std::vector<Resources::Vertex> vertexArray;

        for (int i = 0; i < sectorAmount; ++i)
        {
            float curAngle = 2.f * M_PI * (i % sectorAmount) / (1.f * sectorAmount);
            float nextAngle = 2.f * M_PI * ((i - 1) % sectorAmount) / (1.f * sectorAmount);

            Vec3 curVtxPos = Vec3(radius * cosf(curAngle), height, radius * sinf(curAngle));
            Vec3 nextVtxPos = Vec3(radius * cosf(nextAngle), height, radius * sinf(nextAngle));

            int indexStartingSize = vertexArray.size();

            vertexArray.push_back(Resources::Vertex{ nextVtxPos, nextVtxPos, Vec2(i * 1.f / sectorAmount, 1.f) });
            vertexArray.push_back(Resources::Vertex{ curVtxPos, curVtxPos, Vec2((i + 1) * 1.f / sectorAmount, 1.f) });
            vertexArray.push_back(Resources::Vertex{ Vec3(nextVtxPos.x, -nextVtxPos.y, nextVtxPos.z), Vec3(nextVtxPos.x, -nextVtxPos.y, nextVtxPos.z), Vec2(i * 1.f / sectorAmount, 0.f) });
            vertexArray.push_back(Resources::Vertex{ Vec3(curVtxPos.x, -curVtxPos.y, curVtxPos.z), Vec3(curVtxPos.x, -curVtxPos.y, curVtxPos.z), Vec2((i + 1) * 1.f / sectorAmount, 0.f) });

            indexArray.push_back(indexStartingSize + 1);
            indexArray.push_back(indexStartingSize + 3);
            indexArray.push_back(indexStartingSize + 2);

            indexArray.push_back(indexStartingSize + 0);
            indexArray.push_back(indexStartingSize + 1);
            indexArray.push_back(indexStartingSize + 2);
        }

        for (int j = 0; j < sectorAmount; ++j)
        {
            float theta0 = ((j + 0) / (float)sectorAmount) * M_PI; //sectorAmount
            float theta1 = ((j + 1) / (float)sectorAmount) * M_PI;

            for (int i = 0; i < sectorAmount; ++i)
            {
                float phi0 = ((i + 0) / (float)sectorAmount) * 2.f * M_PI;
                float phi1 = ((i + 1) / (float)sectorAmount) * 2.f * M_PI;

                Vec3 c0 = getSphericalCoords(radius, theta0, phi0);
                Vec3 c1 = getSphericalCoords(radius, theta0, phi1);
                Vec3 c2 = getSphericalCoords(radius, theta1, phi1);
                Vec3 c3 = getSphericalCoords(radius, theta1, phi0);

                if (j < sectorAmount / 2)
                {
                    c0 += Vec3(0.f, height, 0.f);
                    c1 += Vec3(0.f, height, 0.f);
                    c2 += Vec3(0.f, height, 0.f);
                    c3 += Vec3(0.f, height, 0.f);
                }
                else
                {
                    c0 -= Vec3(0.f, height, 0.f);
                    c1 -= Vec3(0.f, height, 0.f);
                    c2 -= Vec3(0.f, height, 0.f);
                    c3 -= Vec3(0.f, height, 0.f);
                }

                int curIndex = vertexArray.size();

                vertexArray.push_back({ c0, c0, Vec2((float)i / sectorAmount, 1.f - (float)(j) / sectorAmount) });
                vertexArray.push_back({ c1, c1, Vec2((float)(i + 1) / sectorAmount,  1.f - (float)(j) / sectorAmount) });
                vertexArray.push_back({ c2, c2, Vec2((float)(i + 1) / sectorAmount,  1.f - (float)((j + 1) % sectorAmount) / sectorAmount) });
                vertexArray.push_back({ c3, c3, Vec2((float)i / sectorAmount,  1.f - (float)((j + 1) % sectorAmount) / sectorAmount) });

                indexArray.push_back(curIndex);
                indexArray.push_back(curIndex + 1);
                indexArray.push_back(curIndex + 2);

                indexArray.push_back(curIndex);
                indexArray.push_back(curIndex + 2);
                indexArray.push_back(curIndex + 3);
            }
        }

        ComputeTangents(vertexArray);

        Resources::Model* capsule = new Resources::Model("");
        Resources::Subobject sub = Resources::Subobject();
        Resources::Subobject& ref = sub;
        ref.IndexBuffer = indexArray;
        ref.VertexBuffer = vertexArray;
        ref.SetBuffers();
        capsule->mSubobjects.push_back(ref);
        return capsule;
    }
}