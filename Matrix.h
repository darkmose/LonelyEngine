#pragma once


static class Matrix
{
private:
	static float ratio;
public:
	static float angle;
	static mat4 view, model;
	static mat4 projection;
	static mat4 GenPerspective(float, float);
	static mat4 GenOrtho(float, float, float, float, float, float);
};

mat4 Matrix::view = mat4();;
mat4 Matrix::model = mat4();;
mat4 Matrix::projection;
float Matrix::angle = 70.f;
float Matrix::ratio;


inline mat4 Matrix::GenPerspective(float w, float h)
{
	ratio = w / h;
	return perspective(angle, ratio, 0.1f, 400.0f);
}
inline mat4 Matrix::GenOrtho(float l, float r, float b, float t, float near, float far)
{
	return ortho(l,r,b,t,near,far);	
}








