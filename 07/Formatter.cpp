#include "Formatter.h"

std::string Formatter::format(const std::string& s, const std::vector<std::string>& _Sargs)
{
	std::string res;
	std::string pos;
	size_t _pos;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] == '{')
		{
			pos = "";
			while (++i < s.size() && '0' <= s[i] && s[i] <= '9')
				pos+=s[i];
			if (pos.empty() || s[i] != '}')
				throw std::runtime_error("Can't be found '}'");
			_pos = std::stoi(pos);
			if (_pos >= _Sargs.size()) 
				throw std::runtime_error("Arg position out of range");
			res += _Sargs[_pos];
		}
		else if(s[i] != '}')
			res+=s[i];
		else
			throw std::runtime_error("Wrong '}'");
	}
	return res;
}
