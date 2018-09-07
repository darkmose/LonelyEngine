#pragma once


class MatGl
{
private:
	mat4 projection;
	float angle = 70.f;
	float ratio;

public:
	mat4 view, model;
	MatGl(float, float, bool);
	mat4 GlobalMatrix();
};


	MatGl::MatGl(float width,float height, bool isPerspective)
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
		model = mat4();
		view = mat4();
	}

	mat4 MatGl::GlobalMatrix()
	{
		return projection*view*model;
	}







