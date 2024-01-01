#include <App.hpp>

namespace Core
{
	App::~App()
	{
		mThreadManager.Destroy();
		mRscManager->Clear();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}

	bool App::Init(AppInitializer& init)
	{

		mWidth = init.width; mHeight = init.height;
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, init.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, init.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		// glfw Window creation
		// --------------------
		Window = glfwCreateWindow(init.width, init.height, init.name, NULL, NULL);
		if (Window == NULL)
		{
			std::cout << "Failed to create GLFW Window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(Window);
		glfwSetFramebufferSizeCallback(Window, init.framebuffer_size_callback);


		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}


		GLint flags = 0;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(init.glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glfwGetWindowSize(Window, &mWidth, &mHeight);
		mCam.Aspect = mWidth / mHeight;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		return true;
	}

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void App::processInput(GLFWwindow* Window)
	{
		mPlayer.PlayerInput.moveForward = glfwGetKey(Window, mPlayer.keyBoardInput.moveForward) == GLFW_PRESS;
		mPlayer.PlayerInput.moveBackward = glfwGetKey(Window, mPlayer.keyBoardInput.moveBackward) == GLFW_PRESS;
		mPlayer.PlayerInput.moveLeft = glfwGetKey(Window, mPlayer.keyBoardInput.moveLeft) == GLFW_PRESS;
		mPlayer.PlayerInput.moveRight = glfwGetKey(Window, mPlayer.keyBoardInput.moveRight) == GLFW_PRESS;
		mPlayer.PlayerInput.moveUp = glfwGetKey(Window, mPlayer.keyBoardInput.moveUp) == GLFW_PRESS;
		mPlayer.PlayerInput.moveDown = glfwGetKey(Window, mPlayer.keyBoardInput.moveDown) == GLFW_PRESS;

		if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			mInWindow = true;
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			mInWindow = false;
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}


		double newMouseX, newMouseY;
		float deltaX, deltaY;
		glfwGetCursorPos(Window, &newMouseX, &newMouseY);
		if (mFirstMouse)
		{
			mMouseX = newMouseX;
			mMouseY = newMouseY;
			mFirstMouse = false;
		}
		deltaX = (float)(newMouseX - mMouseX);
		deltaY = (float)(mMouseY - newMouseY);
		mMouseX = newMouseX;
		mMouseY = newMouseY;

		if (!mInWindow)
			return;

		mCam.CamInputs.deltaX = deltaX;
		mCam.CamInputs.deltaY = deltaY;
	}

	void App::InitResourcesMultithread()
	{
		mThreadManager.Init();

		mRscManager = Resources::ResourceManager::GetInstance();

		start = std::chrono::steady_clock::now();

		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Shader>("shader", "Resources/Shaders/shader.vert:Resources/Shaders/shader.frag"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Shader>("shaderGooch", "Resources/Shaders/shader.vert:Resources/Shaders/gooch-Shading.frag"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Shader>("shaderCel", "Resources/Shaders/shader.vert:Resources/Shaders/cel-shading.frag"));

		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Shader>("Outline", "Resources/Shaders/shader.vert:Resources/Shaders/Outline.frag"));

		mShaderProgram = mRscManager->Get<Resources::Shader>("shader")->GetShaderProgram();
		mOutline = mRscManager->Get<Resources::Shader>("Outline")->GetShaderProgram();

		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Shader>("normalMapShader", "Resources/Shaders/normalMapping.vert:Resources/Shaders/normalMapping.frag"));
		mNormalMapShaderProgram = mRscManager->Get<Resources::Shader>("normalMapShader")->GetShaderProgram();

		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Shader>("parallaxMapShader", "Resources/Shaders/normalMapping.vert:Resources/Shaders/parallaxMapping.frag"));
		mParallaxMapShaderProgram = mRscManager->Get<Resources::Shader>("parallaxMapShader")->GetShaderProgram();

		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("barkTex", "Resources/Textures/bark_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("furTex", "Resources/Textures/fur_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("gravelTex", "Resources/Textures/gravel_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("pebblesTex", "Resources/Textures/pebbles_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("TerracottaTex", "Resources/Textures/Terracotta_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("brickTex", "Resources/Textures/bricks_color.jpg"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("toyTex", "Resources/Textures/toy_box_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("PlasticTex", "Resources/Textures/Vent_003_basecolor.jpg"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("IceTex", "Resources/Textures/Ice_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("LeatherPaddedTex", "Resources/Textures/Leather_Padded_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("LeatherPerforatedTex", "Resources/Textures/Bacteria_001_COLOR.jpg"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("RockTex", "Resources/Textures/Rock_color.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("SapphireTex", "Resources/Textures/Sapphire_color.png"));

		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("barkNormal", "Resources/NormalMaps/bark_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("furNormal", "Resources/NormalMaps/fur_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("gravelNormal", "Resources/NormalMaps/gravel_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("pebblesNormal", "Resources/NormalMaps/pebbles_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("TerracottaNormal", "Resources/NormalMaps/Terracotta_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("brickNormal", "Resources/NormalMaps/bricks_normal.jpg"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("toyNormal", "Resources/NormalMaps/toy_box_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("PlasticNormal", "Resources/NormalMaps/Vent_003_normal.jpg"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("IceNormal", "Resources/NormalMaps/Ice_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("LeatherPaddedNormal", "Resources/NormalMaps/Leather_Padded_normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("LeatherPerforatedNormal", "Resources/NormalMaps/Bacteria_001_NORM.jpg"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("RockNormal", "Resources/NormalMaps/Rock_Normal.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("SapphireNormal", "Resources/NormalMaps/Sapphire_normal.png"));

		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("barkHeight", "Resources/HeightMaps/Bark_Height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("furHeight", "Resources/HeightMaps/Fur_height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("gravelHeight", "Resources/HeightMaps/Gravel_Height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("pebblesHeight", "Resources/HeightMaps/Pebbles_Height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("TerracottaHeight", "Resources/HeightMaps/Terracotta_height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("brickHeight", "Resources/HeightMaps/bricks_height.jpg"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("toyHeight", "Resources/HeightMaps/toy_box_height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("PlasticHeight", "Resources/HeightMaps/Vent_003_height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("IceHeight", "Resources/HeightMaps/Ice_height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("LeatherPaddedHeight", "Resources/HeightMaps/Leather_Padded_height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("LeatherPerforatedHeight", "Resources/HeightMaps/Bacteria_001_DISP.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("RockHeight", "Resources/HeightMaps/Rock_Height.png"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Texture>("SapphireHeight", "Resources/HeightMaps/Sapphire_height.png"));

		//mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Model>("sponza", "Resources/Obj/trueSponza/sponza.obj"));
		mThreadManager.RsrcToLoadQueue.push(mRscManager->Create<Resources::Model>("cubeObj", "Resources/Obj/cube.obj"));

		mResourceLoadedCount = mRscManager->Size();		
	}

	void App::InitScene()
	{
		mPlayer.Object = new DataStructure::GameObject();
		mGraph.Objects.push_back(mPlayer.Object);

		//1
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(0.f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("toyTex"),
					mRscManager->Get<Resources::Texture>("toyNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(0.f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("toyTex"),
					mRscManager->Get<Resources::Texture>("toyNormal"),
					mRscManager->Get<Resources::Texture>("toyHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(0.f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("toyTex")
				)
			)
		);

		//2
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-1.5f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("barkTex"),
					mRscManager->Get<Resources::Texture>("barkNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-1.5f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("barkTex"),
					mRscManager->Get<Resources::Texture>("barkNormal"),
					mRscManager->Get<Resources::Texture>("barkHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-1.5f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("barkTex")
				)
			)
		);

		//3
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(1.5f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("pebblesTex"),
					mRscManager->Get<Resources::Texture>("pebblesNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(1.5f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("pebblesTex"),
					mRscManager->Get<Resources::Texture>("pebblesNormal"),
					mRscManager->Get<Resources::Texture>("pebblesHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(1.5f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("pebblesTex")
				)
			)
		);

		//4
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-3.f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("gravelTex"),
					mRscManager->Get<Resources::Texture>("gravelNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-3.f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("gravelTex"),
					mRscManager->Get<Resources::Texture>("gravelNormal"),
					mRscManager->Get<Resources::Texture>("gravelHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-3.f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("gravelTex")
				)
			)
		);

		//5
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-4.5f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("brickTex"),
					mRscManager->Get<Resources::Texture>("brickNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-4.5f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("brickTex"),
					mRscManager->Get<Resources::Texture>("brickNormal"),
					mRscManager->Get<Resources::Texture>("brickHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-4.5f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("brickTex")
				)
			)
		);

		//6
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(3.f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("TerracottaTex"),
					mRscManager->Get<Resources::Texture>("TerracottaNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(3.f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("TerracottaTex"),
					mRscManager->Get<Resources::Texture>("TerracottaNormal"),
					mRscManager->Get<Resources::Texture>("TerracottaHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(3.f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("TerracottaTex")
				)
			)
		);

		//7
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(4.5f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("furTex"),
					mRscManager->Get<Resources::Texture>("furNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(4.5f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("furTex"),
					mRscManager->Get<Resources::Texture>("furNormal"),
					mRscManager->Get<Resources::Texture>("furHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(4.5f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("furTex")
				)
			)
		);

		//8
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(6.f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("IceTex"),
					mRscManager->Get<Resources::Texture>("IceNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(6.f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("IceTex"),
					mRscManager->Get<Resources::Texture>("IceNormal"),
					mRscManager->Get<Resources::Texture>("IceHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(6.f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("IceTex")
				)
			)
		);

		//9
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(7.5f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("LeatherPaddedTex"),
					mRscManager->Get<Resources::Texture>("LeatherPaddedNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(7.5f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("LeatherPaddedTex"),
					mRscManager->Get<Resources::Texture>("LeatherPaddedNormal"),
					mRscManager->Get<Resources::Texture>("LeatherPaddedHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(7.5f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("LeatherPaddedTex")
				)
			)
		);

		//10
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(9.f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("LeatherPerforatedTex"),
					mRscManager->Get<Resources::Texture>("LeatherPerforatedNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(9.f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("LeatherPerforatedTex"),
					mRscManager->Get<Resources::Texture>("LeatherPerforatedNormal"),
					mRscManager->Get<Resources::Texture>("LeatherPerforatedHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(9.f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("LeatherPerforatedTex")
				)
			)
		);

		//11
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-6.f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("PlasticTex"),
					mRscManager->Get<Resources::Texture>("PlasticNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-6.f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("PlasticTex"),
					mRscManager->Get<Resources::Texture>("PlasticNormal"),
					mRscManager->Get<Resources::Texture>("PlasticHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-6.f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("PlasticTex")
				)
			)
		);

		//12
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-7.5f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("RockTex"),
					mRscManager->Get<Resources::Texture>("RockNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-7.5f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("RockTex"),
					mRscManager->Get<Resources::Texture>("RockNormal"),
					mRscManager->Get<Resources::Texture>("RockHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-7.5f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("RockTex")
				)
			)
		);

		//13
		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-9.f, 0.f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mNormalMapShaderProgram,
					mRscManager->Get<Resources::Texture>("SapphireTex"),
					mRscManager->Get<Resources::Texture>("SapphireNormal")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-9.f, -1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mParallaxMapShaderProgram,
					mRscManager->Get<Resources::Texture>("SapphireTex"),
					mRscManager->Get<Resources::Texture>("SapphireNormal"),
					mRscManager->Get<Resources::Texture>("SapphireHeight")
				)
			)
		);

		mGraph.Objects.push_back(
			new DataStructure::GameObject
			(
				Physics::Transform(Vec3(-9.f, 1.1f, 1.5f)),
				LowRenderer::Mesh(
					mRscManager->Get<Resources::Model>("cubeObj"),
					mShaderProgram,
					mRscManager->Get<Resources::Texture>("SapphireTex")
				)
			)
		);

		for (DataStructure::GameObject* obj : mGraph.Objects)
			mGraph.RootChildren.push_back({ obj });

		for(float i = -3.f; i < 4.f; i += 1.f)
			mPointLights.push_back(LowRenderer::PointLight(Vec3(i * 3.f), Vec4(0.25f, 0.25f, 0.25f), Vec4(0.5f, 0.5f, 0.5f), Vec4(1.f, 1.f, 1.f), Vec3(1.f, 0.045f, 0.0075f)));

		mDirectionalLights.push_back(LowRenderer::DirectionalLight(Vec3(1.f, 1.f, 1.f), Vec3(0.1f, 0.1f, 0.1f), Vec3(0.5f, 0.5f, 0.5f)));
		mDirectionalLights.push_back(LowRenderer::DirectionalLight(Vec3(-1.f, -1.f, -1.f), Vec3(0.1f, 0.1f, 0.1f), Vec3(0.5f, 0.5f, 0.5f)));
	}

	void App::DisplaySliderFloatPosObject(std::vector<DataStructure::SceneNode> &Children, std::string index)
	{
		if (Children.size() > 0)
		{
			std::string name = "object";
			for (int j = 0; j < Children.size(); j++)
			{
				ImGui::DragFloat3((name + index + std::to_string(j)).c_str(), &Children[j].Object->Transform.Position.x, 0.5f, -10.f, 10.f, "%.3f", 0);
				DisplaySliderFloatPosObject(Children[j].Children, index + std::to_string(j));
			}
		}
	}

	void App::ThreadManagement()
	{
		if (!mThreadManager.RsrcToInitList.empty() && mThreadManager.IsOpenGLListAvailable.load() == 0)
		{
			int tmpAccessValue = ++mThreadManager.IsOpenGLListAvailable;

			if (tmpAccessValue == 1)
			{
				for (Resources::IResource* rsrc : mThreadManager.RsrcToInitList)
				{
					if (rsrc->State == Resources::ResourceState::RS_LOADED)
					{
						rsrc->OpenGLInit();
						rsrc->State = Resources::ResourceState::RS_INIT;
					}
				}
				while (!mThreadManager.RsrcToInitList.empty() && mThreadManager.RsrcToInitList.front()->State == Resources::ResourceState::RS_INIT)
				{
					mThreadManager.RsrcToInitList.pop_front();
					--mResourceLoadedCount;
				}

				mThreadManager.IsOpenGLListAvailable.store(0);
			}
		}
		else if (mResourceLoadedCount == 0 && mThreadManager.RsrcToInitList.empty() && mThreadManager.RsrcToLoadQueue.empty())
		{
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::cout << "elapsed time: " << elapsed_seconds.count() * 1000 << "ms\n";
			mResourceLoadedCount = -1;
		}
	}
	
	void App::Update()
	{
		// =======init Outline bool value=========
		isOutLine = false;

		// =========init IMGUI=============
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float currentFrame = glfwGetTime();
		mDeltaTime = currentFrame - mLastFrame;
		mLastFrame = currentFrame;
		glfwPollEvents();

		glfwGetWindowSize(Window, &mWidth, &mHeight);
		mCam.Aspect = (float)mWidth / (float)mHeight;
		if (mMenu.gameState == GS_MULTITHREAD)
		{
			if(!isInit)
			{
				InitResourcesMultithread();
				InitScene();
				isInit = true;
			}

			// Imgui Menu
			processInput(Window);
			if (ImGui::Begin("Config"))
			{
				if (ImGui::CollapsingHeader("Objects", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
				{
					std::string name = "object";
					for (int i = 1; i < mGraph.RootChildren.size(); i++)
					{
						ImGui::DragFloat3((name + std::to_string(i)).c_str(), &mGraph.RootChildren[i].Object->Transform.Position.x, .2f, -50.f, 50.f, "%.1f", 0);
						DisplaySliderFloatPosObject(mGraph.RootChildren[i].Children, std::to_string(i));
					}
				}
				if (ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
				{
					if (ImGui::CollapsingHeader("PointLights", ImGuiTreeNodeFlags_NoAutoOpenOnLog | ImGuiTreeNodeFlags_Bullet))
					{
						std::string name = "PointLight[";
						for(int i = 0; i < mPointLights.size(); ++i)
							ImGui::DragFloat3((name + std::to_string(i) + ']').c_str(), &mPointLights[i].Position.x, .2f, -50.f, 50.f, "%.1f", 0);
					}
					if (ImGui::CollapsingHeader("DirectionalLights", ImGuiTreeNodeFlags_NoAutoOpenOnLog | ImGuiTreeNodeFlags_Bullet))
					{
						std::string name = "DirLight[";
						for (int i = 0; i < mDirectionalLights.size(); ++i)
							ImGui::DragFloat3((name + std::to_string(i) + ']').c_str(), &mDirectionalLights[i].Direction.x, .2f, -50.f, 50.f, "%.1f", 0);
					}
				}
				if (ImGui::CollapsingHeader("Shader", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
				{
					ImGui::Checkbox("Cel-Shading", &mMenu.shaderCheckBox);
					ImGui::Checkbox("Gooch-Shading", &goochload);
				}
				ImGui::DragFloat3("Cam", &mCam.Position.x, .2f, -50.f, 50.f, "%.1f", 0);
			}



			ImGui::End();

			// input
			// -----
			if (mResourceLoadedCount == -1 && glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				if (mMenu.gameState == GS_MULTITHREAD)
					mThreadManager.Destroy();
				mRscManager->Clear();
				mGraph.Destroy();
				mDirectionalLights.clear();
				mSpotLights.clear();
				mPointLights.clear();
				isInit = false;
				mMenu.gameState = GS_MAIN_MENU;
			}
			else if(isInit)
			{
				if (mMenu.gameState == GS_MULTITHREAD)
					ThreadManagement();

				mCam.Update(mDeltaTime, mPlayer.Object->Transform.Position);

				mPlayer.Update(mDeltaTime, mCam);

				// render
				// ------
				glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				static float time = 0.f;

				for(LowRenderer::PointLight& pLight : mPointLights)
					pLight.Position = Vec3(pLight.Position.x, 2.f * sinf(time));

				time += mDeltaTime;

				glEnable(GL_CULL_FACE);

				glCullFace(GL_BACK);
				glDepthFunc(GL_LESS);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				mGraph.Update(mCam, mDirectionalLights, mPointLights, mSpotLights);

				isOutLine = true;
				if (isOutLine)
				{
					glCullFace(GL_FRONT);
					glDepthFunc(GL_LEQUAL);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

					glLineWidth(3);

					mGraph.Update(mCam, mDirectionalLights, mPointLights, mSpotLights, isOutLine, Vec4(0));
				}
				if (mMenu.shaderCheckBox)
				{
					if (!celInit && isInitBasic && !goochInit)
					{
						mShaderProgram = mRscManager->Get<Resources::Shader>("shaderCel")->GetShaderProgram();
						for (int i = 0; i < mGraph.Objects.size(); i++)
						{
							mGraph.Objects[i]->Mesh.mShaderProgram = mShaderProgram;
						}
						celInit = true;
						goochInit = false;
						isInitBasic = false;
					}
				}
				else if (goochload)
				{
					if (!celInit && isInitBasic && !goochInit)
					{
						mShaderProgram = mRscManager->Get<Resources::Shader>("shaderGooch")->GetShaderProgram();
						for (int i = 0; i < mGraph.Objects.size(); i++)
						{
							mGraph.Objects[i]->Mesh.mShaderProgram = mShaderProgram;
						}
						celInit = true;
						goochInit = false;
						isInitBasic = false;
					}
				}
				else
				{
					if (celInit && !isInitBasic && !goochInit)
					{
						mShaderProgram = mRscManager->Get<Resources::Shader>("shader")->GetShaderProgram();
						for (int i = 0; i < mGraph.Objects.size(); i++)
						{
							if(i%3==0)
								mGraph.Objects[i]->Mesh.mShaderProgram = mShaderProgram;
							if (i % 3 == 1)
								mGraph.Objects[i]->Mesh.mShaderProgram = mNormalMapShaderProgram;
							if (i % 3 == 2)
								mGraph.Objects[i]->Mesh.mShaderProgram = mParallaxMapShaderProgram;
						}
						celInit = false;
						goochInit = false;
						isInitBasic = true;
					}
				}	
			}
		}
		else
		{
			ImGui::Begin("Menu", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowPos(ImVec2(0, 0), 0);
			ImGui::SetWindowSize(ImVec2(mWidth, mHeight), 0);
			mMenu.Render(Window, mWidth, mHeight);
			
			ImGui::End();
		}

		if (mMenu.gameState == GS_OPTION)
		{
			ImGui::Begin("Option", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowSize(ImVec2(mWidth, mHeight), 0);
			ImGui::SetWindowPos(ImVec2(0, 0), 0);
			mMenu.RenderOption(mPlayer, Window,mWidth, mHeight);
			if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				mMenu.gameState = GS_MAIN_MENU;
			ImGui::End();
		}

		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(Window);
	}
}