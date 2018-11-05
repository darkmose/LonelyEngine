#pragma once
static class Primitive
{
private:
	static const VertexVec verts_Plane;
	static const VertexVec verts_Cube;
	static const VertexVec verts_Quad;
public:

	static const GLfloat _Plane_Pos[];
	static const GLfloat _Plane_Norm[];
	static const GLfloat _Plane_TexCoords[];

	static const GLfloat _Cube_Pos[];
	static const GLfloat _Cube_Norm[];
	static const GLfloat _Cube_TexCoords[];

	static const GLfloat _Quad_Pos[];
	static const GLfloat _Quad_TexCoords[];

	static const GLfloat Empty[1];

	static Mesh* Cube();
	static Mesh* Plane();
	static Mesh* Quad();
};

const GLfloat Primitive::Empty[1] = {0};

const GLfloat Primitive::_Plane_Pos[] = {
	-1.0f,  1.0f,  0.0f,
	-1.0f, -1.0f,  0.0f,
	1.0f, -1.0f,  0.0f, 
	-1.0f,  1.0f,  0.0f, 
	1.0f, -1.0f,  0.0f,
	1.0f,  1.0f,  0.0f 
};
const GLfloat Primitive::_Plane_Norm[]= {
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f
};
const GLfloat Primitive::_Plane_TexCoords[] = {
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f
};

const VertexVec Primitive::verts_Plane = { Primitive::_Plane_Pos, Primitive::_Plane_Norm, Primitive::_Plane_TexCoords };

const GLfloat Primitive::_Cube_Pos[] = {
	-0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f, 
	0.5f, -0.5f, -0.5f, 
	0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f, 

	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f, 
	0.5f,  0.5f,  0.5f, 
	0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f, 

	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f,

	0.5f,  0.5f,  0.5f,  
	0.5f, -0.5f, -0.5f,  
	0.5f,  0.5f, -0.5f, 
	0.5f, -0.5f, -0.5f, 
	0.5f,  0.5f,  0.5f,  
	0.5f, -0.5f,  0.5f,  

	-0.5f, -0.5f, -0.5f, 
	0.5f, -0.5f, -0.5f, 
	0.5f, -0.5f,  0.5f, 
	0.5f, -0.5f,  0.5f,  
	-0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f, -0.5f, 

	-0.5f,  0.5f, -0.5f, 
	0.5f,  0.5f,  0.5f, 
	0.5f,  0.5f, -0.5f, 
	0.5f,  0.5f,  0.5f,  
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f
};
const GLfloat Primitive::_Cube_Norm[] = {
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,

	0.0f,  0.0f, 1.0f,
	0.0f,  0.0f, 1.0f,
	0.0f,  0.0f, 1.0f,
	0.0f,  0.0f, 1.0f,
	0.0f,  0.0f, 1.0f,
	0.0f,  0.0f, 1.0f,

	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,

	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,

	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,

	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f
};
const GLfloat Primitive::_Cube_TexCoords[] = {
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f, 
    1.0f, 1.0f, 
	0.0f, 0.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f, 
	0.0f, 1.0f, 
	0.0f, 0.0f, 

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f, 
	0.0f, 1.0f,

	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 1.0f, 
	0.0f, 0.0f
};

const VertexVec Primitive::verts_Cube = { Primitive::_Cube_Pos, Primitive::_Cube_Norm, Primitive::_Cube_TexCoords };

const GLfloat Primitive::_Quad_Pos[]= {
	-1.0f,  1.0f, 
	-1.0f, -1.0f,
	1.0f, -1.0f, 
	-1.0f,  1.0f,
	1.0f, -1.0f, 
	1.0f,  1.0f
};
const GLfloat Primitive::_Quad_TexCoords[] = {
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f
};

const VertexVec Primitive::verts_Quad = { Primitive::_Quad_Pos, Primitive::Empty, Primitive::_Quad_TexCoords };


Mesh* Primitive::Cube()
{
	return new Mesh(verts_Cube);
}

Mesh* Primitive::Plane()
{
	return new Mesh(verts_Plane);
}

Mesh* Primitive::Quad()
{
	return new Mesh(verts_Quad);
}

