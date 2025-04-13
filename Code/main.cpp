#define GLEW_STATIC
#include "ThirdPartyLib/GL/glew.h"
#include "ThirdPartyLib/GLFW/glfw3.h"
#include <thread>
#include "ThirdPartyLib/imGUI/imgui.h"
#include "ThirdPartyLib/imGUI/imgui_impl_glfw.h"
#include "ThirdPartyLib/imGUI/imgui_impl_opengl3.h"
#include "XEngine.h"
#include "XEngineBegin.h"
#include "GameSettings.h"
#include "Input.h"
#include "XTime.h"
#include "XThreadPool.h"
#include "BufferManager.h"
#include "SceneManager.h"

bool XEngine::gameState = true;

int threadPool();

int main() {

	//openGl初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//窗口初始化
	GLFWwindow *pWindow = glfwCreateWindow((int)XGameWindowSize().x_,
		(int)XGameWindowSize().y_, "XIAOBAILEN", nullptr, nullptr);
	if (pWindow == nullptr) {
		XENGINE_LOG("窗口创建失败");
		glfwTerminate();
	}
	//绑定上下文
	glfwMakeContextCurrent(pWindow);

	//glew初始化
	glewExperimental = true;
	if (glewInit() != 0) {
		XENGINE_LOG("glew初始化失败");
		glfwTerminate();
	}

	//设置渲染显示窗口大小
	//glViewport(0, 0, 800, 450);
	//GameSettings::getGameSettingsObj()->setViewportSize(800, 450);
	glViewport(0, 0, (int)XGameViewportSize().x_, (int)XGameViewportSize().y_);

	//设置事件回调
	glfwSetCursorPosCallback(pWindow, &Input::mousePosCallback);
	glfwSetScrollCallback(pWindow, &Input::mouseScrollCallback);

	//创建绑定ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

	//设置颜色风格
	ImGui::StyleColorsDark();

	//将渲染绑定到OpenGl
	ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	
	XEngine* pEngine = XEngine::getInstance();
	SceneManager* pSence_manager = SceneManager::getSceneManagerObj();
	BufferManager* pBuffer_manager = BufferManager::getBufferManagerObj();

	XTime* pTimer = XTime::getTimeObj();
	
	WorldConstructor wc;

	std::thread thread_ThreadPool(threadPool);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(pWindow) && XEngine::getGameState())
	{
		pTimer->renderBegin();

		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//XENGINE_LOG("logic");
		pSence_manager->runThread();

		//XENGINE_LOG("Physics");
		pSence_manager->updatePhysWorld();

		//XENGINE_LOG("collision");
		pSence_manager->collisionDetection();

		//XENGINE_LOG("show");
		pSence_manager->show();

		pSence_manager->postProcessing();



		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Sence Objects Info");
			if (ImGui::Button("print time")) {
				XENGINE_LOG(pTimer->getTime());
			}
			if (ImGui::Button("Max Fps")) {
				GameSettings::setGameMaxFPS(2000.0f);
			}
			if (ImGui::Button("Min Fps")) {
				GameSettings::setGameMaxFPS(60.0f);
			}
			if (ImGui::Button("randInt")) {
				XENGINE_LOG(XMath::randInt(-300,300));
			}
			if (ImGui::Button("randFloat")) {
				XENGINE_LOG(XMath::randFloat(-300, 300));
			}
			ImGui::Text("DeltaTime:            %.7f s", pTimer->getDeltaTime());
			ImGui::Text("Undormancy DeltaTime: %.7f s", pTimer->getUndormancyDeltaTime());
			ImGui::Text("Lowest  Time:         %.7f s", pTimer->dLowestTime_);
			ImGui::Text("Highest Time:         %.7f s", pTimer->dHighestTime_);
			ImGui::Text("FPS:                  %.1f fps", pTimer->dFPS_);
			ImGui::Text("Object count:         %d", pSence_manager->getCurrentObjectCount());
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		glfwSwapBuffers(pWindow);
		
		pBuffer_manager->createBuffers();
		pSence_manager->deleteObject();


		pTimer->renderEnd();
		pTimer->limitFPS();
		pTimer->fpsSampling();
	}

	XEngine::exitGame();
	glfwDestroyWindow(pWindow);
	glfwTerminate();
	std::this_thread::sleep_for(std::chrono::milliseconds((long long)10));

	thread_ThreadPool.join();

	return 0;
}

int threadPool()
{
	XThreadPool *xthread_pool = XThreadPool::getThreadPoolObj();
	while (XEngine::getGameState()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(XGameThreadSleepTime));
	};
	return 0;
}
