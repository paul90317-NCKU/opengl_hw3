#ifndef __TREE_NODE_H
#define __TREE_NODE_H
#include "comm.hpp"
#include "ShaderProgram.hpp"
#include "objLoader.hpp"

class tree_node {
public:
	glm::vec3 axi;
	glm::vec3 joint;
	glm::mat4 base;
	std::pair<float, float> range;
	std::vector<tree_node> children;
	tree_node(glm::vec3 _axi,glm::vec3 _joint,glm::mat4 _base,std::pair<float,float> _range) {
		axi = _axi;
		joint = _joint;
		base = _base;
		range = _range;
	}
	tree_node& add_child(tree_node tn) {
		children.push_back(tn);
		return *this;
	}
	void draw(ShaderProgram& sp,glm::mat4 parent,int n,float alpha) {
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(range.first*alpha+(1-alpha)*range.second),axi);
		glm::mat4 t = glm::translate(glm::mat4(1.0f), -joint);
		glm::mat4 tback = glm::translate(glm::mat4(1.0f), joint);
		parent = parent * tback * rot * t;
		glm::mat4 trans = parent * base;
		sp
			.UniformMatrix4fv("trans", glm::value_ptr(trans));
		glDrawArrays(GL_TRIANGLES, 0, n);
		for (auto c : children) {
			c.draw(sp, parent, n,alpha);
		}
	}
};


#endif