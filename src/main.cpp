#include<stdio.h>
#include<stdlib.h>

#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<card.h>

#define ImGuiWindow(name, code) ImGui::Begin(name);\
	code\
	ImGui::End()

void err_exit(int condition){
	if(condition) exit(1);
}

static void glfw_error_callback(int error, const char* description){
	fprintf(stderr, "GLFW Error: %d: %s\n", error, description);
}

GLFWwindow* setup_glfw(){
	glfwSetErrorCallback(glfw_error_callback);


	err_exit(!glfwInit());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* win;
	err_exit(!(win = glfwCreateWindow(1024, 768, "Imgui Test", NULL, NULL)));

	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);

	err_exit(glewInit() != GLEW_OK);

	return win;
}

void set_glfw_viewport(GLFWwindow* win){
	int width,height;
	glfwGetFramebufferSize(win, &width, &height);
	glViewport(0, 0, width, height);
}



void imgui_newframe(){
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void clear_gl(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void init_imgui(GLFWwindow* win){
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void end_imgui(){
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void end_glfw(GLFWwindow* win){
	glfwDestroyWindow(win);
	glfwTerminate();
}




int main(int argc, char** argv){

	GLFWwindow* win = setup_glfw();

	Card* card = new Card(
			new ManaValue(0,0,0,0,0,2));
	card->to_string();

	init_imgui(win);

	while(!glfwWindowShouldClose(win)){
		glfwPollEvents();

		imgui_newframe();

		static int counter = 0;
		ImGuiWindow("Hello, World!",
				if(ImGui::Button("Button")) counter++;
				ImGui::SameLine();
				ImGui::Text("Counter = %d", counter);
				ImGui::Text("lets go!!!"););

		ImGui::Render();

		set_glfw_viewport(win);
		clear_gl();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(win);
	}

	end_imgui();

	end_glfw(win);
	return 0;
}
