#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

class MatGl
{

private:
	mat4 projection;
	float angle = 70.f;
	float ratio;

public:
	

	mat4 view, model;
	MatGl(float width,float height, bool isPerspective)
	{
		if (isPerspective)
		{
			ratio = width / height;
			projection = perspective(angle, ratio, 0.1f, 100.0f);
		}
		else
		{
			projection = ortho(0.0f, width, 0.0f, height, 0.1f, 100.0f);
		}
		modelMatrix();
		viewMatrix();
	}

	~MatGl() 
	{
		projection._null;
		view._null;
		model._null;
	}

	mat4 GlobalMatrix(float _time)
	{
		return projection*view*model*RotateMatrix(_time*100,vec3(1,1,0));
	}
protected:

	void modelMatrix()
	{
		model = RotateMatrix(-55.5f, vec3(1, 0, 0));
	}

	void viewMatrix()
	{
		view = translate(view, vec3(-1.5f, 0.0f, -5.0f));
	}


	mat4 RotateMatrix(float _angle, vec3 axis)
	{
		mat4 transform;
		return rotate(transform, _angle, axis);
	}

	mat4 ScaleMatrix(vec3 _scale)
	{
		mat4 transform;
		return scale(transform, _scale);;
	}

	mat4 TranslateMatrix(vec3 _translate)
	{
		mat4 transform;
		return translate(transform, _translate);
	}
};










