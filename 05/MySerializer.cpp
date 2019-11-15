#include "MySerializer.h"

//////////////Serializer//////////////

Error MySerializer::process(bool value)
{
	if (value)
		out_ << "true";
	else
		out_ << "false";
	out_ << Separator;
	return Error::NoError;
}

Error MySerializer::process(uint64_t value)
{
	out_ << value << Separator;
	return Error::NoError;
}

//////////////Deserializer//////////////////

Error MyDeserializer::process(bool& value)
{
	std::string text;
	in_ >> text;

	if (text == "true")
		value = true;
	else if (text == "false")
		value = false;
	else
		return Error::CorruptedArchive;

	return Error::NoError;
}

Error MyDeserializer::process(uint64_t& value)
{
	std::string text;
	in_ >> text;
	uint64_t _value = 0;
	for (int i = text.size()-1, k = 1; i >= 0; --i, k *= 10)
	{
		if (text[i] >= '0' && text[i] <= '9')
			_value += k * (text[i] - 48);
		else
			return Error::CorruptedArchive;
	}
	if(text == "") return Error::CorruptedArchive;
	value = _value;
	return Error::NoError;
}