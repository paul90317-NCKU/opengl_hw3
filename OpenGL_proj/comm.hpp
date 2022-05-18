#ifndef __COMM_HPP
#define __COMM_HPP

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <vector>
#include <stb/stb_image.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace mymat {
	inline glm::mat4 I() {
		return glm::mat4(1.0f);
	}
	inline glm::mat4 translate(float x, float y, float z) {
		return glm::translate(I(), glm::vec3(x, y, z));
	}
	inline glm::mat4 translate(glm::vec3 position) {
		return glm::translate(I(), position);
	}
	inline glm::mat4 rotate(glm::vec3 joint,glm::vec3 axis, float degree) {
		//the rotation of this obj
		glm::mat4 rot = glm::rotate(I(), degree, axis);
		//make the O match the joint
		glm::mat4 t = glm::translate(I(), -joint);
		//make the O move back, so that it's seen like that rotate around J
		glm::mat4 tback = glm::translate(I(), joint);
		return tback * rot * t;
	}
	inline glm::mat4 rotate(glm::vec3 axis, float degree) {
		return glm::rotate(I(), degree, axis);;
	}
	inline glm::mat4 scale(glm::vec3 _scale) {
		return glm::scale(I(), _scale);
	}
	inline glm::mat4 scale(float x,float y,float z) {
		return glm::scale(I(), glm::vec3(x, y, z));
	}
	inline glm::mat4 scale(float _scale) {
		return glm::scale(I(), glm::vec3(_scale));
	}
}
class drange {
public:
	float dmin;
	float dmax;
	drange(float _dmin,float _dmax) {
		dmax = _dmax;
		dmin = _dmin;
	}
	drange() {
		dmax = 0.0f;
		dmin = 0.0f;
	}
	float get_max() {
		return std::max(dmax, dmin);
	}
	float get_min() {
		return std::min(dmax, dmin);
	}
};

#endif