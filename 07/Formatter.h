#pragma once
#include <iostream>
#include <sstream>
#include <vector>

class Formatter
{
public:
	template <class... ArgsT>
	std::string operator()(const std::string& s,ArgsT&&... args)
	{
		std::vector<std::string> Sargs;
		process(Sargs, std::forward<ArgsT>(args)...);
		return format(s, Sargs);
	}
private:
	//process uses variadic templates
	template<class T>
	void process(std::vector<std::string>& _Sargs, T&& object)
	{
		std::stringstream stream;
		stream << object;
		_Sargs.push_back(stream.str());
		return;
	}

	template<class T, class... ArgsT>
	void process(std::vector<std::string>& _Sargs, T&& object, ArgsT&&... args)
	{
		process(_Sargs, object);
		process(_Sargs, std::forward<ArgsT>(args)...);
		return;
	}

	std::string format(const std::string& s, const std::vector<std::string>& _Sargs);
};
