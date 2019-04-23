#pragma once
#include "Matrix.h"

class Transform 
{
private:
	mat4 mat_position;
	mat4 mat_rotation;
	mat4 mat_scale;
public:
	vec3 _position;
	vec3 _scale;
	__readonly static vec3 up;
	__readonly static vec3 right;
	__readonly static vec3 forward;

	Transform();
	void TranslatePos(vec3);
	void MoveGlobalMatrix();
	void Rotate(float, vec3);
	void Scale(vec3);
};


inline Transform::Transform()
{
	_position = vec3(0, 0, 0);
	_scale = vec3(1, 1, 1);
}

void Transform::TranslatePos(vec3 __pos)
{
	_position += __pos;
}

inline void Transform::MoveGlobalMatrix()
{
	mat4 _model = translate(mat4(), _position);
	Matrix::model = _model * mat_rotation * mat_scale;
}

inline void Transform::Rotate(float angle, vec3 axis)
{
	mat_rotation = rotate(mat4(), angle, axis);
}

inline void Transform::Scale(vec3 scaleVec)
{
	_scale = scaleVec;
	mat_scale = scale(mat4(), _scale);
}



 vec3 Transform::up = vec3(0,1,0);
 vec3 Transform::right = vec3(1,0,0);
 vec3 Transform::forward = vec3(0,0,1);
