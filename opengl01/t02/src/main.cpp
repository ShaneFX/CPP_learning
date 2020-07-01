#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"

int w = 1600;
int h = 1200;



int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(w, h, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	{

		Camera cam(glm::vec3(0.0, 0.8, 4.0), glm::vec3(0.0, 0.0, 0.0));

		Model box("res/model/toy.obj");
		VertexArray va;
		unsigned int count = box.GetVbData().size();
		float *vbdata{ new float[count] };
		memcpy(vbdata, &box.GetVbData()[0], count * sizeof(float));
		VertexBuffer vb(vbdata, box.GetVbData().size() * sizeof(float));
		VertexBufferLayout layout = box.GetLayout();
		delete[] vbdata;
		va.AddBuffer(vb, layout);

		unsigned int *da{ new unsigned int[count/8]};
		memcpy(da, &box.GetIbData()[0], count / 8 * sizeof(GLuint));
		IndexBuffer ib(da, box.GetIbData().size());
		delete[] da;

		glm::mat4 model = cam.get_model_matrix(glm::vec3(0.0, 0.0, 0.0f));
		glm::mat4 proj = cam.get_projection_matrix();
		glm::mat4 view = cam.get_view_matrix();


		Shader shader("res/shader/Basic.shader");
		shader.Bind();

		Texture texture("res/texture/rubbertoy01.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();
			glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
			shader.Bind();

			{
				GLfloat currentFrame = glfwGetTime();
				model = glm::rotate(model, currentFrame / 1000.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Drawit(va, count/8, shader);
				//glBindVertexArray(va.getid());
				//glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glfwSwapBuffers(window);
			glfwPollEvents();

		}

	}
	glfwTerminate();
	return 0;
}