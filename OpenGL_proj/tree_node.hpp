#ifndef __TREE_NODE_H
#define __TREE_NODE_H
#include "comm.hpp"
#include "ShaderProgram.hpp"
#include "objLoader.hpp"

class tree_node {
public:
	static tree_node* hight_light_point;
	bool is_hight_light=false;

	glm::vec3 axis;
	glm::vec3 joint;
	drange animation_drange;
	drange limit_drange;
	glm::mat4 translate;
	glm::mat4 model;
	VertexArray VAO;
	std::vector<tree_node*> children;
	glTexture* texture = NULL;
	float deg_offset = 0.0f;
	tree_node(VertexArray _VAO, glm::mat4 _model,glm::mat4 _translate, glm::vec3 _joint,glm::vec3 _axis,drange _animation_drange,drange _limit_drange) {
		VAO = _VAO;
		model = _model;
		translate = _translate;
		joint = _joint;
		axis = _axis;
		animation_drange = _animation_drange;
		limit_drange = _limit_drange;
	}
	tree_node() {}
	tree_node& add_child(tree_node& tn) {
		children.push_back(&tn);
		return *this;
	}
	void draw(ShaderProgram& sp,glm::mat4 parent,float alpha) {
		float deg = animation_drange.dmin * (1 - alpha) + animation_drange.dmax * alpha;
		deg += deg_offset;
		if (deg > limit_drange.get_max())deg = limit_drange.get_max();
		if (deg < limit_drange.get_min())deg = limit_drange.get_min();
		glm::mat4 rot = mymat::rotate(joint, axis, deg);
		parent = parent * translate * rot;
		glm::mat4 res = parent * model;
		sp
			.UniformMatrix4fv("trans", glm::value_ptr(res));
		VAO.Bind();
		
		if (texture) {
			texture->Bind();
			glDrawArrays(GL_TRIANGLES, 0, VAO.draw_number);
			texture->UnBind();
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, VAO.draw_number);
		}
		
		VAO.UnBind();
		for (auto c : children) {
			c->draw(sp, parent,alpha);
		}
	}
	void draw_hight_light(ShaderProgram& sp, glm::mat4 parent, float alpha) {
		float deg = animation_drange.dmin * (1 - alpha) + animation_drange.dmax * alpha;
		deg += deg_offset;
		if (deg > limit_drange.get_max())deg = limit_drange.get_max();
		if (deg < limit_drange.get_min())deg = limit_drange.get_min();
		glm::mat4 rot = mymat::rotate(joint, axis, deg);
		parent = parent * translate * rot;
		if (hight_light_point && is_hight_light)
			hight_light_point->draw(sp, parent, alpha);
		for (auto c : children) {
			c->draw_hight_light(sp, parent, alpha);
		}
	}
	tree_node& BindTexture(glTexture* tex) {
		texture = tex;
		return *this;
	}
	void deg_inc(float deg,float alpha) {
		if (deg_offset+ animation_drange.dmin * (1 - alpha) + animation_drange.dmax * alpha <= limit_drange.get_max()) {
			deg_offset += deg;
		}
	}
	void deg_dec(float deg,float alpha) {
		if (deg_offset+ animation_drange.dmin * (1 - alpha) + animation_drange.dmax * alpha >= limit_drange.get_min()) {
			deg_offset -= deg;
		}
	}
};


#endif