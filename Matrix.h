#pragma once


static class Matrix
{
private:
	static float ratio;
public:
	static float angle;
	static mat4 view, model;
	static mat4 projection;
	static void SetProjection(float, float, bool);
};

mat4 Matrix::view = mat4();;
mat4 Matrix::model = mat4();;
mat4 Matrix::projection;
float Matrix::angle = 70.f;
float Matrix::ratio;


void Matrix::SetProjection(float w, float h, bool isPerspective) 
{
	if (isPerspective)
	{
		ratio = w / h;
		projection = perspective(angle, ratio, 0.1f, 400.0f);
	}
	else
	{
		projection = ortho(0.0f, w, 0.0f, h, 0.1f, 100.0f);
	}
}








