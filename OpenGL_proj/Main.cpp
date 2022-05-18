#include "comm.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"
#include "glTexture.hpp"
#include "objLoader.hpp"
#include "tree_node.hpp"

struct part_node {
	std::string name;
	tree_node* part;
	part_node(std::string _name, tree_node* _part) {
		name = _name;
		part = _part;
	}
};

int main(int argc,char* argv[]) {
	std::string vertexShader = "BasicVertexShader.glsl";
	std::string fragmentShader = "BasicFragmentShader.glsl";
	int width = 800;
	int height = 800;

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
	glm::mat4 proj = glm::perspective(70.0f, (float)(width / height), 0.1f, 200.0f);
	glm::mat4 model =
		mymat::rotate(glm::vec3(1, 0, 0), 25)
		* mymat::rotate(glm::vec3(0, 1, 0), -45)
		* mymat::scale(0.8);
	glm::mat4 view = mymat::translate(0, 0, -30);
	glm::mat4 mvp = proj * view * model;
		

	ShaderProgram sp3d;
	sp3d
		.AttachShader(fragmentShader.c_str(), GL_FRAGMENT_SHADER)
		.AttachShader(vertexShader.c_str(), GL_VERTEX_SHADER)
		.Link().Use()
		.Uniform1i("objectTexture", 0)
		.UniformMatrix4fv("mvp", glm::value_ptr(mvp));

	VertexArray Cube;
	{
		std::vector<float> posf, norf, texf;
		std::vector<unsigned int> posi, nori, texi;
		std::vector<float> allf;
		int n = objLoader("cube.obj", posf, norf, texf, posi, nori, texi);
		ToBuffer(allf, posf, norf, texf, posi, nori, texi);
		Cube = VertexArray(n);
		Cube.Bind();
		Cube
			.Add(glBuffer(allf.data(), allf.size() * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_STATIC_DRAW))
			.Attrib(0, 3, GL_FLOAT, 8 * sizeof(GLfloat))
			.Attrib(1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)))
			.Attrib(2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)))
			.UnBindAll();// Safe Unbind all object
	}
	
	VertexArray Sword;
	{
		std::vector<float> posf, norf, texf;
		std::vector<unsigned int> posi, nori, texi;
		std::vector<float> allf;
		int n = objLoader("sword.obj", posf, norf, texf, posi, nori, texi);
		ToBuffer(allf, posf, norf, texf, posi, nori, texi);
		Sword = VertexArray(n);
		Sword.Bind();
		Sword
			.Add(glBuffer(allf.data(), allf.size() * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_STATIC_DRAW))
			.Attrib(0, 3, GL_FLOAT, 8 * sizeof(GLfloat))
			.Attrib(1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)))
			.Attrib(2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)))
			.UnBindAll();// Safe Unbind all object
	}

	tree_node body, head, lefthand1, lefthand2, righthand1, righthand2, sword, leftleg1, leftleg2, rightleg1, rightleg2;
	glTexture head_texture(GL_TEXTURE_2D);
	head_texture.Generate("head.jpg").UnBind();

	glTexture skin_texture(GL_TEXTURE_2D);
	skin_texture.Generate("skin.bmp").UnBind();

	glTexture shorts_texture(GL_TEXTURE_2D);
	shorts_texture.Generate("shorts.bmp").UnBind();

	glTexture body_texture(GL_TEXTURE_2D);
	body_texture.Generate("body.bmp").UnBind();

	glTexture sword_texture(GL_TEXTURE_2D);
	sword_texture.Generate("sword.png").UnBind();

	body = tree_node(Cube, mymat::scale(10, 10, 5), mymat::I(),
		glm::vec3(0), glm::vec3(0,1,0), drange(), drange())
		.BindTexture(&body_texture);
	lefthand1 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(-7.5, 1.5, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(-1, 0, 0),
		drange(45, -45), drange(90, -90))
		.BindTexture(&body_texture);
	lefthand2 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(0, - 7, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(-1, 0, 0),
		drange(45, 0), drange(90, 0))
		.BindTexture(&skin_texture);
	sword = tree_node(Sword,
		mymat::rotate(glm::vec3(0, 0, 1), 90)
		* mymat::rotate(glm::vec3(0, 1, 0), -135)
		* mymat::scale(15),
		mymat::translate(0, -2.5, 8),
		glm::vec3(0), glm::vec3(0,0,1)
		, drange(), drange(-90, 90))
		.BindTexture(&sword_texture);
	righthand1 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(7.5, 1.5, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(1, 0, 0),
		drange(45, -45), drange(90, -90))
		.BindTexture(&body_texture);
	righthand2 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(0, -7, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(1, 0, 0),
		drange(0, -45), drange(0, -90))
		.BindTexture(&skin_texture);
	leftleg1 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(-2.5, -8.5, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(1, 0, 0),
		drange(35, -45), drange(45, -90))
		.BindTexture(&shorts_texture);
	leftleg2 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(0, -7, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(1, 0, 0),
		drange(35, 0), drange(90, 0))
		.BindTexture(&skin_texture);
	rightleg1 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(2.5, -8.5, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(-1, 0, 0),
		drange(45, -35), drange(90, -45))
		.BindTexture(&shorts_texture);
	rightleg2 = tree_node(Cube, mymat::scale(5, 7, 5), mymat::translate(0, -7, 0),
		glm::vec3(0, 3.5, 0), glm::vec3(-1, 0, 0),
		drange(0, -35), drange(0, -90))
		.BindTexture(&skin_texture);
	head = tree_node(Cube, mymat::scale(10, 10, 10), mymat::translate(0, 10, 0),
		glm::vec3(0), glm::vec3(0, 1, 0),
		drange(), drange(-90, 90))
		.BindTexture(&head_texture);

	//face right (our view)
	//(right,up,back)
	//the obj is mirror :))
	
	body
		.add_child(
			lefthand1.add_child(
				lefthand2.add_child(
					sword
				)
			)
		).add_child(
			righthand1.add_child(
				righthand2
			)
		).add_child(
			leftleg1.add_child(
				leftleg2
			)
		).add_child(
			rightleg1.add_child(
				rightleg2
			)
		).add_child(
			head
		);
	
	std::vector<part_node>  parts({
		part_node("Head",&head),
		part_node("Right Hand 1",&lefthand1),
		part_node("Right Hand 2",&lefthand2),
		part_node("Left Hand 1",&righthand1),
		part_node("Left Hand 2",&righthand2),
		part_node("Right Leg 1",&leftleg1),
		part_node("Right Leg 2",&leftleg2),
		part_node("Left Leg 1",&rightleg1),
		part_node("Left Leg 2",&rightleg2),
		part_node("Sword",&sword)
		});
	int part_choosen_i = 0;
	double lastframTime = glfwGetTime();
	bool q_press = false;
	bool w_press = false;
	bool s_press = false;
	float alpha = 0.0f;
	bool back = false;
	bool stop = true;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//glfwSetMouseButtonCallback(window, mymouse::callback);
	while (!glfwWindowShouldClose(window)) {
		double crntTime = glfwGetTime();
		
		if (crntTime - lastframTime > 0.01f) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if (!stop) {
				if (back) {
					alpha += 0.02f;
					if (alpha > 1.0f)back = false;
				}
				else {
					alpha -= 0.02f;
					if (alpha < 0.0f)back = true;
				}
			}
			//key down event
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				if (q_press == false) {
					stop = !stop;
					q_press = true;
				}
			}
			else q_press = false;
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				if (w_press == false) {
					part_choosen_i--;
					if (part_choosen_i < 0)part_choosen_i = parts.size() - 1;
					std::cout << parts[part_choosen_i].name << "\n";
					w_press = true;
				}
			}
			else w_press = false;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				if (s_press == false) {
					part_choosen_i = (part_choosen_i + 1) % parts.size();
					std::cout << parts[part_choosen_i].name << "\n";
					s_press = true;
				}
			}
			else s_press = false;

			//key press
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				parts[part_choosen_i].part->deg_dec(1,alpha);
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				parts[part_choosen_i].part->deg_inc(1, alpha);
			}

			//mouse press
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				xpos = (xpos - width / 2) / width;
				ypos = (ypos - height / 2) / height;
				float deg = sqrtf(xpos * xpos + ypos * ypos);
				view = view*mymat::rotate(glm::vec3(ypos, xpos, 0), -deg);
				mvp = proj * view * model;
				sp3d.UniformMatrix4fv("mvp", glm::value_ptr(mvp));
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				xpos = (xpos - width / 2) / width;
				ypos = (ypos - height / 2) / height;
				view = mymat::translate(xpos, -ypos, 0) * view;
				mvp = proj * view * model;
				sp3d.UniformMatrix4fv("mvp", glm::value_ptr(mvp));
			}
			body.draw(sp3d, mymat::I() ,alpha);
			glfwSwapBuffers(window);
			lastframTime = crntTime;
		}
		glfwPollEvents();
	}


	sp3d.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}