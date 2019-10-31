#include <iostream>
#include <string>

int isCharIsNum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isCharIsSign(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return 1;
	else
		return 0;
}

using callback = bool(*) (int i);
using callbackntoken = int(*) (std::string &token);
using callbackstoken = std::string(*) (std::string &token);

void find_token(const std::string &pr, const int len,
	callback start, callback end, callbackntoken Ntoken, callbackstoken Stoken) {

	std::string item = "";
	int ci = 1;
	int i = 0;
	start(i);
	while (i < len)
	{

		while (!isCharIsSign( pr[i]))
		{
			item += pr[i];
			if (!(ci && isCharIsNum(pr[i])))
				ci = 0;
			i++;
		}
		//std::cout << item << std::endl;

		if (ci)
		{
			//token is num
			Ntoken(item);
		}
		else
		{
			//token is string
			Stoken(item);
		}
		ci = 1;
		item = "";
		while (i<len && isCharIsSign(pr[i])) ++i;
	}
	end(len - i);
	return;
}
