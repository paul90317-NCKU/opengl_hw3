#ifndef __OBJ_LOADER_HPP
#define __OBJ_LOADER_HPP

#include "comm.hpp"
#include <vector>

struct draw_buffer{
	glm::vec3 pos;
	glm::vec3 nor;
	glm::vec2 tex;
};

int objLoader(const char* filename,\
	std::vector<GLfloat> &posf, std::vector<GLfloat> &norf, std::vector<GLfloat> &texf,\
	std::vector<GLuint> &posi, std::vector<GLuint> &nori, std::vector<GLuint> &texi);

int ToBuffer(std::vector<float> &allf,\
	std::vector<GLfloat> &posf, std::vector<GLfloat> &norf, std::vector<GLfloat> &texf,\
	std::vector<GLuint> &posi, std::vector<GLuint> &nori, std::vector<GLuint> &texi);

#endif