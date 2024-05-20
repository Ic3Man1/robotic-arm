#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

int main() {
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using (in this case 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "RobotArm", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify where OpenGL should work
	glViewport(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);

	// Background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap buffers 
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// Take care of GLFW events
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}