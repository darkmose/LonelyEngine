#pragma once


class Input
{
private:

public:
	static bool GetKey(GLint key);
	static bool GetMod(GLint mod);		
	static bool GetKeyUp(GLint mod);		
	static bool GetKeyDown(GLint mod);		
};


bool Input::GetKey(GLint key)
{
	return Callbacks::getKey(key);
}

bool Input::GetMod(GLint mod)
{
	return Callbacks::getMod(mod);
}
inline bool Input::GetKeyUp(GLint key)
{
	if (glfwGetKey(Callbacks::_window, key) == GLFW_RELEASE)
	{
		if (Callbacks::getState(key) == GLFW_RELEASE)
		{
			Callbacks::setState(key, GLFW_PRESS);
			return true;
		}
	}
	return false;
}

inline bool Input::GetKeyDown(GLint key)
{
	if (glfwGetKey(Callbacks::_window, key) == GLFW_PRESS)
	{
		if (Callbacks::getState(key) == GLFW_PRESS)
		{
			Callbacks::setState(key, GLFW_RELEASE);
			return true;
		}
	}
	return false;
}

