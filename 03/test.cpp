#include <iostream>
#include <string>
#include <cassert>
#include "TokenParser.h"

int TokenIsNum(const int &token)
{
	assert(&token != nullptr);
	std::cout << token << std::endl;
	return token;
}

std::string TokenIsString(const std::string &token)
{
	assert(token != "");
	assert(&token != nullptr);
	std::cout << token << std::endl;
	return token;
}

bool StartParse(int st)
{
	assert(st == 0);
	std::cout << "StartParse " << !st << std::endl;
	return st == 0;
}

bool EndParse(int st)
{
	assert(st == 0);
	std::cout << "EndParse " << !st << std::endl;
	return st == 0;
}

int main() {

	std::string pr;
	/*
	//read input
	getline(std::cin, pr);
	find_token(pr,size(pr),StartParse,EndParse,TokenIsNum,TokenIsString);
	*/
	pr = "";
	find_token(pr, size(pr), StartParse, EndParse, TokenIsNum, TokenIsString);

	pr = "          ";
	find_token(pr, size(pr), StartParse, EndParse, TokenIsNum, TokenIsString);

	pr = "asd dsa 123 asd 23 123a42 ";
	find_token(pr, size(pr), StartParse, EndParse, TokenIsNum, TokenIsString);

	pr = "ilay8!$%\o3wr7ynqwoir		e928374oq c0234 nv2m34oim2u3c 4p2394872 mo;";
	find_token(pr, size(pr), StartParse, EndParse, TokenIsNum, TokenIsString);

	pr = "1\t3 23 2 0";
	find_token(pr, size(pr), StartParse, EndParse, TokenIsNum, TokenIsString);

	std::cout << "Test Success!" << std::endl;
	system("pause");
	return 0;
}
