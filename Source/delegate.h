#pragma once
#include <functional>
#include <vector>

using namespace std;

template<typename... Type>
class delegate
{
	typedef function<void(Type...)> Func;
private:
	int id = 0;
	vector<Func> funcs;
public:
	int Add(Func func)
	{
		funcs.push_back(func);
		return id++;
	}
	void Remove(unsigned char id)
	{
		funcs.erase(funcs.begin() + id);
	}
	int Size() 
	{
		return funcs.size();
	}
	void operator()(Type... param)
	{
		for_each(funcs.begin(), funcs.end(), [&param...](Func fun)
			{
				fun(param...);
			});
	}

	void operator+=(const Func func)
	{
		this->funcs.push_back(func);
	}
};

