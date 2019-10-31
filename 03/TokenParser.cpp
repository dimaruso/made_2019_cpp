#include <iostream>
#include <string>
#include <deque>

namespace MyParser
{
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

	void find_token(const std::string &pr, const int len, std::deque <std::string>& r,
		callback start, callback end, callbackntoken Ntoken, callbackstoken Stoken) {

		std::string item = "";
		//std::deque <std::string> r;
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
				r.push_back(item);
				Ntoken(item);
			}
			else
			{
				//token is string
				r.push_back(item);
				Stoken(item);
			}
			ci = 1;
			item = "";
			while (i<len && isCharIsSign(pr[i])) ++i;
		}
		end(len - i);
		return;
	}

}


int TokenIsNum(std::string &token)
{
	std::cout << token << std::endl;
	return std::stoi(token);
}

std::string TokenIsString(std::string &token)
{
	std::cout << token << std::endl;
	return token;
}

bool StartParse(int i)
{
	std::cout << "StartParse " << bool(i == 0) << std::endl;
	return i == 0;
}

bool EndParse(int i)
{
	std::cout << "EndParse " << bool(i==0) << std::endl;
	return i == 0;
}
using namespace MyParser;
int main() {

	//read input
	std::string pr;

	getline(std::cin, pr);

	std::deque <std::string> r;

	find_token(pr,size(pr),r,StartParse,EndParse,TokenIsNum,TokenIsString);
		/*
	while (!r.empty())
	{
		std::cout << r.front() << std::endl;
		r.pop_front();
	}
	*/
	//system("pause");
	return 0;
}
