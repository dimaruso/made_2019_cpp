#pragma once
#include <iostream>
#include <sstream>

enum class Error
{
	NoError,
	CorruptedArchive
};

class MySerializer
{
	static constexpr char Separator = ' ';
public:
	explicit MySerializer(std::ostream& out): 
		out_(out)
	{
	}
	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}
	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}
private:
	std::ostream& out_;
	// process использует variadic templates
	Error process(bool object);
	Error process(uint64_t object);

	template<class T>
	Error process(T&& object)
	{
		return Error::CorruptedArchive;
	}

	template<class T, class... ArgsT>
	Error process(T&& object, ArgsT&&... args)
	{
		if (process(object) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		return process(std::forward<ArgsT>(args)...);
	}
};


class MyDeserializer
{
	static constexpr char Separator = ' ';
public:

	explicit MyDeserializer(std::istream& in) :
		in_(in)
	{
	}
	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}
	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}

private:
	std::istream& in_;
	// process использует variadic templates
	Error process(bool& object);
	Error process(uint64_t& object);

	template<class T>
	Error process(T&& object)
	{
		return Error::CorruptedArchive;
	}

	template<class T, class... ArgsT>
	Error process(T&& object, ArgsT&&... args)
	{
		if (process(object) == Error::CorruptedArchive)
			return Error::CorruptedArchive;

		process(std::forward<ArgsT>(args)...);
		return Error::NoError;
	}
};