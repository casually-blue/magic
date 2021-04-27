#include<stdio.h>
#include<stdlib.h>

#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

void err_exit(int condition){
	if(condition) exit(1);
}

const char* glsl_version = "#version 330";

static void glfw_error_callback(int error, const char* description){
	fprintf(stderr, "GLFW Error: %d: %s\n", error, description);
}

void setup_glfw(){
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

int main(int argc, char** argv){
	glfwSetErrorCallback(glfw_error_callback);

	err_exit(!glfwInit());

	setup_glfw();

	GLFWwindow* win = glfwCreateWindow(1024, 768, "Imgui Test", NULL, NULL);

	err_exit(win == NULL);

	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);

	err_exit(glewInit() != GLEW_OK);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	while(!glfwWindowShouldClose(win)){
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			static int counter = 0;
			ImGui::Begin("Hello, World!");

			if(ImGui::Button("Button"))
				counter++;

			ImGui::SameLine();
			ImGui::Text("Counter = %d", counter);

			ImGui::End();
		}

		ImGui::Render();

		int width, height;

		glfwGetFramebufferSize(win, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(win);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(win);
	glfwTerminate();

	return 0;
}
