#pragma once
#include <functional>
#include <vector>

using namespace std;

template<typename... Type>
class delegate
{
	typedef function<void(Type...)> Func;
private:
	vector<Func> funcs;
public:
	void Add(Func func)
	{
		funcs.push_back(func);
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


