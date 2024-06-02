#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "texture.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.2f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.2f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};


int main() {
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using (in this case 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Robotic Arm", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Bring the window into current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify where OpenGL should work
	glViewport(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);

	
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// gets id of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	Texture cat("cat1.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	cat.texUnit(shaderProgram, "tex0", 0);

	// IMGUI

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		shaderProgram.Activate();


		int window_width, window_height;
		glfwGetWindowSize(window, &window_width, &window_height);


		ImVec2 window_pos = ImVec2(0, window_height * 0.75f);
		ImVec2 window_size = ImVec2(window_width, window_height * 0.25f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

		int button_pos_x = 80, button_pos_y1 = 25, button_pos_y2 = 110;
		ImVec2 button_size = ImVec2(80, 80);

		ImGui::Begin("Robot Settings");

		ImGui::SetCursorPos(ImVec2(button_pos_x, button_pos_y1));
		if (ImGui::Button("Start learning", ImVec2(160, 80))) {

		}

		ImGui::SetCursorPos(ImVec2(button_pos_x, button_pos_y2));
		if (ImGui::Button("Finish learning", ImVec2(160, 80))) {

		}

		ImGui::SetCursorPos(ImVec2(button_pos_x + 165, button_pos_y1));
		if (ImGui::Button("Execute", ImVec2(160, 165))) {

		}

		ImGui::SetCursorPos(ImVec2(button_pos_x + 330, button_pos_y1));
		if (ImGui::Button("Manual mode", ImVec2(160, 80))) {

		}

		ImGui::SetCursorPos(ImVec2(button_pos_x + 330, button_pos_y1 + 85));
		ImGui::Text("Button 1/2 - Axis 1\nButton 3/4 - Axis 2\nButton 5/6 - Axis 3");
		ImGui::SetCursorPos(ImVec2(button_pos_x + 330 + 165 + 30, button_pos_y1 + 45));
		ImGui::Text("MANIPULATOR COORDINATES:\n\nX:\nY:\nZ:");

		int text_x = 10, text_y = 70;
		static char buf[128] = "";

		ImGui::PushItemWidth(50);
		ImGui::SetCursorPos(ImVec2(text_x, text_y));
		ImGui::InputText("X", buf, IM_ARRAYSIZE(buf));
		ImGui::SetCursorPos(ImVec2(text_x, text_y + 25));
		ImGui::InputText("Y", buf, IM_ARRAYSIZE(buf));
		ImGui::SetCursorPos(ImVec2(text_x, text_y + 50));
		ImGui::InputText("Z", buf, IM_ARRAYSIZE(buf));
		ImGui::PopItemWidth();

		ImGui::SetCursorPos(ImVec2(text_x, text_y + 75));
		if (ImGui::Button("accept", ImVec2(50, 20))) {

		}

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// assigns a value to the uniform, in this case increases the size of triangles by 50%
		glUniform1f(uniID, 0.5f);
		
		cat.Bind();
		// bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap buffers 
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	cat.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}