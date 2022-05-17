#include "comm.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"
#include "glTexture.hpp"
#include "objLoader.hpp"
#include "tree_node.hpp"


int width = 800;
int height = 800;
int vertex_count;

void dfs(aiNode* root,int deep=0) {
	for (int i = 0; i < deep; i++) {
		printf("\t");
	}
	printf("%s\n", root->mName.C_Str());
	for (int i = 0; i < root->mNumChildren; i++) {
		dfs(root->mChildren[i], deep + 1);
	}
}

glm::mat4 ai_to_glm_mat4(aiMatrix4x4 m) {
	glm::mat4 ret(1.0f);

	ret[0][0] = m.a1;
	ret[0][1] = m.a2;
	ret[0][2] = m.a3;
	ret[0][3] = m.a4;
	
	ret[1][0] = m.b1;
	ret[1][1] = m.b2;
	ret[1][2] = m.b3;
	ret[1][3] = m.b4;

	ret[2][0] = m.c1;
	ret[2][1] = m.c2;
	ret[2][2] = m.c3;
	ret[2][3] = m.c4;

	ret[3][0] = m.d1;
	ret[3][1] = m.d2;
	ret[3][2] = m.d3;
	ret[3][3] = m.d4;

	return ret;
}

int main(int argc,char* argv[]) {
	std::string texture = "uv.png";
	std::string vertexShader = "BasicVertexShader.glsl";
	std::string fragmentShader = "BasicFragmentShader.glsl";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Hello Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	glm::mat4 I(1.0f);
	glm::mat4 rotation = glm::rotate(I, glm::radians((float)(50.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view = glm::translate(I, glm::vec3(0.0f, 0.0f, -200.0f)) * glm::scale(I, glm::vec3(0.15f));
	glm::mat4 proj = glm::perspective(glm::radians(180.0f), (float)(width / height), 0.1f, 500.0f);
	glm::mat4 mvp = proj * view;//* model(trivial)

	ShaderProgram shaderProgram;
	shaderProgram
		.AttachShader(fragmentShader.c_str(), GL_FRAGMENT_SHADER)
		.AttachShader(vertexShader.c_str(), GL_VERTEX_SHADER)
		.Link().Use()
		.Uniform1i("objectTexture", 0)
		.UniformMatrix4fv("mvp", glm::value_ptr(mvp));

	std::vector<float> posf, norf, texf;
	std::vector<unsigned int> posi, nori, texi;
	std::vector<float> allf;
	vertex_count = objLoader("cube.obj", posf, norf, texf, posi, nori, texi);
	ToBuffer(allf, posf, norf, texf, posi, nori, texi);

	VertexArray VAO;
	VAO.Bind();
	VAO
		.Add(glTexture(GL_TEXTURE_2D)
			.Generate(texture.c_str()))
		.Add(glBuffer(allf.data(), allf.size() * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_STATIC_DRAW))
		.Attrib(0, 3, GL_FLOAT, 8 * sizeof(GLfloat))
		.Attrib(1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)))
		.Attrib(2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)))
		.UnBindAll();// Safe Unbind all object
	VAO.Bind();

	

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	tree_node root(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::scale(I, glm::vec3(5.0f, 10.0f, 10.0f)),std::pair<float,float>(0.0f,0.0f));
	root
		.add_child(
			tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -5.0f, 2.5f), glm::translate(I, glm::vec3(0.0f, -8.5f, 2.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(1700.0f, -2400.0f))
			.add_child(tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -12.0f, 2.5f), glm::translate(I, glm::vec3(0.0f, -15.5f, 2.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(1700.0f, 0.0f)))
		)
		.add_child(
			tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -5.0f, -2.5f), glm::translate(I, glm::vec3(0.0f, -8.5f, -2.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(-2400.0f, 1700.0f))
			.add_child(tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -12.0f, -2.5f), glm::translate(I, glm::vec3(0.0f, -15.5f, -2.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(0.0f, 1700.0f)))
		)
		.add_child(
			tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 5.0f, 7.5f), glm::translate(I, glm::vec3(0.0f, 1.5f, 7.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(-1700.0f, 1700.0f))
			.add_child(tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -2.5f, 7.5f), glm::translate(I, glm::vec3(0.0f, -5.5f, 7.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(-600.0f, 0.0f)))
		)
		.add_child(
			tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 5.0f, -7.5f), glm::translate(I, glm::vec3(0.0f, 1.5f, -7.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(1700.0f, -1700.0f))
			.add_child(tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -2.5f, -7.5f), glm::translate(I, glm::vec3(0.0f, -5.5f, -7.5f)) * glm::scale(I, glm::vec3(5.0f, 7.0f, 5.0f)), std::pair<float, float>(0.0f, -600.0f)))
		)
		.add_child(
			tree_node(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::translate(I, glm::vec3(0.0f, 10.0f, 0.0f)) * glm::scale(I, glm::vec3(10.0f, 10.0f, 10.0f)), std::pair<float, float>(0.0f, 0.0f))
		);

	double prevTime = glfwGetTime();
	float alpha = 0.0f;
	bool back = false;
	while (!glfwWindowShouldClose(window)) {
		double crntTime = glfwGetTime();
		if (crntTime - prevTime > 0.01f) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			mvp = mvp * rotation;
			shaderProgram
				.UniformMatrix4fv("mvp", glm::value_ptr(mvp));
			if (back) {
				alpha += 0.02f;
				if (alpha > 1.0f)back = false;
			}
			else {
				alpha -= 0.02f;
				if (alpha < 0.0f)back = true;
			}
			
			root.draw(shaderProgram, I, vertex_count,alpha);
			glfwSwapBuffers(window);
			prevTime = crntTime;
		}
		glfwPollEvents();
	}


	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}