#include <Resources/Subobject.hpp>
namespace Resources
{
	Subobject::Subobject():
		VAO(-1),
		mVBO(-1),
		mEBO(-1)
	{

	}

	Subobject::~Subobject()
	{
		VertexBuffer.clear();
		IndexBuffer.clear();
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &mVBO);
		glDeleteBuffers(1, &mEBO);
	}

	void Subobject::SetBuffers()
	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------

		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		glGenVertexArrays(1, &VAO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, VertexBuffer.size() * sizeof(Resources::Vertex), VertexBuffer.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer.size() * sizeof(uint32_t), IndexBuffer.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Resources::Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Resources::Vertex), (void*)sizeof(Vec3));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Resources::Vertex), (void*)(2 * sizeof(Vec3)));
		glEnableVertexAttribArray(2);
		// tangent attribute
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Resources::Vertex), (void*)(2 * sizeof(Vec3) + sizeof(Vec2)));
		glEnableVertexAttribArray(3);
	}
}