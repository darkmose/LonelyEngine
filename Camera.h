#pragma once

mat4* view;

vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraPos(0.7f,1,4);
vec3 cameraTarget = cameraPos + cameraFront;
vec3 direction = normalize(cameraPos - cameraTarget);
vec3 cameraRight = normalize(cross(vec3(0, 1, 0), direction));
vec3 cameraUp = normalize(cross(cameraTarget, cameraRight));


void View() 
{	
	*view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
