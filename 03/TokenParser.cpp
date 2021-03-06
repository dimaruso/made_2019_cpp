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

void find_token(const std::string &pr, const int len,
	void(*start)(int i), void(*end)(int i),
	void(*Ntoken)(const int &token),
	void(*Stoken)(const std::string &token)) 
{
	std::string item = "";
	int ci = 1;
	int i = 0;
	start(i);
	while (i < len)
	{
		while (i < len && isCharIsSign(pr[i])) ++i;

		while (i< len && !isCharIsSign( pr[i]))
		{
			item += pr[i];
			if (!(ci && isCharIsNum(pr[i])))
				ci = 0;
			i++;
		}
		if (item != "")

		if (ci)
		{
			//token is num
			Ntoken(std::stoi(item));
		}
		else
		{
			//token is string
			Stoken(item);
		}
		ci = 1;
		item = "";
	}
	end(len - i);
	return;
}
