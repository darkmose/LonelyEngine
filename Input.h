#pragma once

class Input
{
private:

public:
	static bool GetKey(GLint key);
	static bool GetMod(GLint mod);		
};


bool Input::GetKey(GLint key)
{
	return Callbacks::getKey(key);
}

bool Input::GetMod(GLint mod)
{
	return Callbacks::getMod(mod);
}