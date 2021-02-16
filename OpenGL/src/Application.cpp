#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Styling/IconLoader.h"
#include "Utilities/Time.h"
//#include "Skybox.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

double scrollOffset;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	scrollOffset = yoffset;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "OpenGL Test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//glfwSwapInterval(1);

	SetWindowIcon(window, "resources/textures/lizard.png");
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	

	if (glewInit() != GLEW_OK)
		return -1;
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float positions[] = {
		 -50.0f, -50.0f,  0.0f, 0.0f,//0
		  50.0f, -50.0f,  1.0f, 0.0f,//1
		  50.0f,  50.0f,  1.0f, 1.0f,//2
		 -50.0f,  50.0f,  0.0f, 1.0f//3
	};
	
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	IndexBuffer ib(indices, 6);
	//-------------------Model View Projection -------------------------
	glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -100.0f, 100.0f);

	glm::vec3 translation(0, 0, 0);
	glm::vec3 translationB(100, 100, 0);



	glm::mat4 view = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));

	glm::mat4 mvp = proj * view * model;
	
	Shader shader("resources/shaders/Basic.glsl");
	shader.Bind();
	shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.SetUniformMat4f("u_MVP", mvp);

	Texture texture("resources/textures/lizard.png");
	texture.Bind();
	shader.SetUniform<int>("u_Texture", 0); //0 is for slot

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
	
	//---------INPUT---------
	Time time;
	double mouseX = 0.0f, mouseY = 0.0f, lastMouseX = 0.0f, lastMouseY = 0.0f, mouseOffsetX = 0.0f, mouseOffsetY = 0.0f, scrollOffsetY = 0.0f;


	glm::vec4 image_color(1.0f, 1.0f, 1.0f, 1.0f);
	Transform transform;
	Transform transform_ortho;
	Camera camera(glm::vec3(0,0,30), 70.0f, 1280.0f/720.0f, 0.01f, 1000.0f);
	Camera camera_ortho(0.0f, 720.0f, 0.0f, 1280.0f);

	//Skybox skybox("resources/skyboxes/galaxy_skybox_blue");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		shader.Bind();
		{//perspective camera
			//model = glm::translate(glm::mat4(1.0f), translation);
			//mvp = proj * view * transform.GetModel();
			mvp = camera.GetViewProjection() * transform.GetModel();
			shader.SetUniform<glm::mat4>("u_MVP", mvp);
			renderer.Draw(va, ib, shader);
		}

		camera.MoveCamera(window, time.deltaTime, mouseOffsetX, mouseOffsetY, scrollOffset);
		camera_ortho.MoveCamera(window, time.deltaTime, mouseOffsetX, mouseOffsetY, scrollOffset);
		scrollOffset = 0.0f;

		{//orthographic camera
			model = glm::translate(glm::mat4(1.0f), translationB);
			//mvp = proj * view * model;
			//mvp = camera_ortho.GetViewProjection() * model;
			mvp = camera_ortho.GetViewProjection() * transform_ortho.GetModel();
			shader.SetUniform<glm::mat4>("u_MVP", mvp);
			renderer.Draw(va, ib, shader);
		}

		shader.SetUniform<glm::mat4>("u_MVP", mvp);
		renderer.Draw(va, ib, shader);

		va.Bind();
		ib.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		float c[4];
		ImGui::Begin("Inspector Window", nullptr, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMainMenuBar()) {
			ImGui::Text("FPS: %.3f   Frametime: %.3f ms/frame", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
			ImGui::EndMainMenuBar();
		}
		

		if (ImGui::CollapsingHeader("Color")) {
			ImGui::ColorPicker4("Color", &image_color.x);
		}

		shader.SetUniform<glm::vec4>("u_Color", image_color);
		//------------Inspector-----------
		{
			camera.ShowInspector();
			camera_ortho.ShowInspector();

			transform.ShowInspector();
			transform_ortho.ShowInspector();
		}
		//-------------TIME---------------
		{
			time.CalculateDelta();
		}
		//-------------INPUT--------------
		{
			glfwGetCursorPos(window, &mouseX, &mouseY);
			mouseOffsetX = mouseX - lastMouseX;
			mouseOffsetY = mouseY - lastMouseY;
			lastMouseX = mouseX;
			lastMouseY = mouseY;
		}

		shader.SetUniform<glm::mat4>("u_MVP", mvp);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}