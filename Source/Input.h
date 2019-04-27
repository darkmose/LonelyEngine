#pragma once

namespace Input {

	vec2 mousePos() 
	{
		return Callbacks::mousePos;
	}

	bool GetKey(GLint key)
	{
		return Callbacks::getKey(key);
	}

	bool GetMod(GLint mod)
	{
		return Callbacks::getMod(mod);
	}
	inline bool GetKeyUp(GLint key)
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

	inline bool GetKeyDown(GLint key)
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

};