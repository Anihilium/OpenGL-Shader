#include <Resources/Model.hpp>

namespace Resources
{
	Model::Model(const char* p_path)
	{
		path = p_path;
		State = ResourceState::RS_NOT_LOADED;
	}

	Model::~Model()
	{
		
	}

	void Model::LoadData()
	{
		if (path[0] == '\0')
			return;

		FILE* file;

		fopen_s(&file, path, "r");
		ASSERT(file != nullptr, "Could not open file")

		std::vector<Vec3> vertexPositions;
		std::vector<Vec2> vertexTextureCoord;
		std::vector<Vec3> vertexNormal;

		char header;
		Vec3 vPos;
		Vec2 vTex;
		Vec3 vNorm;


		Subobject currSubobject = Subobject();
		mSubobjects.push_back(currSubobject);
		Subobject* ref = &mSubobjects[0];

		do
		{
			header = fgetc(file);
			if (header == 'v')
			{
				header = fgetc(file);
				switch (header)
				{
				case ' ':
					if (!fscanf_s(file, "%f %f %f\n", &vPos.x, &vPos.y, &vPos.z))
						return;
					vertexPositions.push_back(vPos);
					break;
				case 't':
					if(!fscanf_s(file, " %f %f\n", &vTex.x, &vTex.y))
						return;
					vertexTextureCoord.push_back(vTex);
					break;
				case 'n':
					if(!fscanf_s(file, " %f %f %f\n", &vNorm.x, &vNorm.y, &vNorm.z))
						return;
					vertexNormal.push_back(vNorm);
					break;
				default:
					break;
				}
			}
			else if (header == 'f')
			{
				header = fgetc(file);
				while (header != '\n' && header != EOF)
				{
					int vtxData[3];
					fscanf_s(file, "%d/%d/%d", &vtxData[0], &vtxData[1], &vtxData[2]);
					Vertex vtx = { vertexPositions[vtxData[0] - 1], vertexNormal[vtxData[2] - 1], vertexTextureCoord[vtxData[1] - 1] };
					ref->IndexBuffer.push_back(ref->IndexBuffer.size());
					ref->VertexBuffer.push_back(vtx);
					header = fgetc(file);
				}

				//Code needed for normal mapping
				unsigned int vertexAmount = ref->VertexBuffer.size();
				Vec3 tangent;
				Vec3 edge1 = ref->VertexBuffer[vertexAmount - 2].Position - ref->VertexBuffer[vertexAmount - 3].Position;
				Vec3 edge2 = ref->VertexBuffer[vertexAmount - 1].Position - ref->VertexBuffer[vertexAmount - 3].Position;
				Vec2 deltaUV1 = ref->VertexBuffer[vertexAmount - 2].TextureUV - ref->VertexBuffer[vertexAmount - 3].TextureUV;
				Vec2 deltaUV2 = ref->VertexBuffer[vertexAmount - 1].TextureUV - ref->VertexBuffer[vertexAmount - 3].TextureUV;

				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
				tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
				tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

				tangent = tangent.Normalize();

				for (unsigned int i = 1; i <= 3; ++i)
					ref->VertexBuffer[vertexAmount - i].Tangent = tangent;
				//
			}
			else if (header == 'o')
			{
				if (!currSubobject.IndexBuffer.empty())
				{
					currSubobject = Subobject();
					mSubobjects.push_back(currSubobject);
					ref = &mSubobjects[mSubobjects.size() - 1];
				}

				while (header != '\n' && header != EOF)
					header = fgetc(file);
			}
			else
				while (header != '\n' && header != EOF)
					header = fgetc(file);
		} while (header != EOF);

		fclose(file);
	}

	void Model::OpenGLInit()
	{
		for(Subobject& sub : mSubobjects)
			sub.SetBuffers();
	}

	void Model::Draw(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights)
	{

	}
}