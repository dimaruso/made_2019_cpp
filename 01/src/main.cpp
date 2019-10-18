#include <iostream>
#include <string>
#include <stack>
#include <deque>

struct myStack
{
	double num;
	char sign;
};

int isCharIsNum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isCharIsSign(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return 1;
	else
		return 0;
}

myStack get_num(const std::string &s, std::deque <myStack>* r)
{
	myStack res;
	myStack item;
	res.sign = '0';
	int lr = 0;
	double c = 0;
	int cnum = 0;
	double unarminus = 1;
	double point = 0;
	for (int i = 0; i < size(s); i++)
	{
		if (isCharIsNum(s[i]))
		{
			cnum = 1;
			if (point > 5)
			{
				c += (s[i] - 48) / point;
				point *= 10;
			}
			else
				c = c * 10 + (s[i] - 48);
		}
		else
			if (s[i] == '.' || s[i] == ',')
			{
				if (cnum && point < 5) point = 10;
				else
				{
					res.sign = '.';
					break;
				}
			}
			else
				if (isCharIsSign(s[i]))
				{
					point = 0;
					if (cnum)
					{

						item.num = c * unarminus;
						item.sign = '1';
						r->push_back(item);

						c = 0;
						cnum = 0;
						unarminus = 1;
						
					}
					else
						if (s[i] == '-' && unarminus == 1)
						{
							unarminus = -1;
						}
						else
						{
							res.sign = '-';
							break;
						}
					if (unarminus != -1)
					{
						item.sign = s[i];
						item.num = 0;
						r->push_back(item);
					}
				}
				else
					if (s[i] == ' ')
					{
					}
					else
					{
						res.sign = 's';
						break;
					}
	}
	if (cnum)
	{
		item.num = c * unarminus;
		item.sign = '1';
		r->push_back(item);


	}
	res.num = lr;
	return res;
}

void trans(std::deque <myStack>* r)
{
	std::stack <myStack> teh;
	int lp = r->size();
	myStack item;
	for(int i = 0;i<lp;i++)
	{
		item = r->front();
		r->pop_front();
		switch (item.sign)
		{
		case '+':
		case '-':
			if (teh.empty())
			{
				teh.push(item);
			}
			else
			
				if (teh.top().sign == '+' || teh.top().sign == '-')//teh.top
				{
					r->push_back(teh.top());
					teh.pop();
					teh.push(item);

				}
				else
					if (teh.top().sign == '*' || teh.top().sign == '/')
					{
						r->push_back(teh.top());
						teh.pop();

						if (! teh.empty())
						{
							r->push_back(teh.top());
							teh.pop();
							
						}
						teh.push(item);
					}
		break;

		case '1':
			r->push_back(item);
			if (i == lp-1)
			{
				while (! teh.empty())
				{
					r->push_back(teh.top());
					teh.pop();
				}
			}
			break;

		case '/':
		case '*':
			if (teh.empty() || teh.top().sign == '+' || teh.top().sign == '-')
			{
				teh.push(item);

			}
			else
				if (teh.top().sign == '*' || teh.top().sign == '/')
				{
					r->push_back(teh.top());
					teh.pop();
					teh.push(item);
				}
			break;
		}
	}
}

double calc(std::deque <myStack>* pol)
{	

	std::stack <myStack> st;
	int lst = 0;

	myStack item = pol->front();
	pol->pop_front();
	st.push(item);

	while(pol->size() > 0)
	{
		item = pol->front();
		pol->pop_front();

		if (item.sign == '1')
		{
			st.push(item);
		}
		else
		{
			myStack b = st.top();
			st.pop();
			myStack a = st.top();
			st.pop();
			switch (item.sign)
			{
			case '+':
				a.num += b.num;
				st.push(a);
				break;
			case '-':
				a.num -= b.num;
				st.push(a);
				break;
			case '*':
				a.num *= b.num;
				st.push(a);
				break;
			case '/':
				a.num /= b.num;
				st.push(a);
				break;
			}
		}
	}
	return st.top().num;
}

myStack get_res(const std::string &pr) {

	//create myStack of operations	
	//myStack* r = (myStack*) malloc(size(pr)*sizeof(myStack));
	std::deque <myStack> r;
	myStack res;
	myStack error = get_num(pr,&r);
	
	if (error.sign == '0')
	{
		//translate to reverse polish notation
		trans(&r);
		//calc res
		res.sign = '0';
		res.num = calc(&r);
	}
	else
	{
		//error output
		res.sign = '1';
		res.num = '0';
	}
	return res;
}

int main() {
	//helper
	std::cout << "write: 'calc + ' ' + equation'";
	std::cout << std::endl;

	//read input
	std::string calc_command;
	std::string pr;

	std::cin >> calc_command;
	getline(std::cin, pr);

	//result
	myStack res;

	//use calc command
	if (calc_command == "calc")
	{
		res = get_res(pr);
		//check error in calc command
		if (res.sign == '0')
		{
			std::cout << res.num << std::endl;
			system("pause");
			return 0;

		}
		else
		{
			std::cout << "error "<< res.sign << std::endl;
			system("pause");
			return -1;
		}

	}
	else
	{
		std::cout << "error command" << std::endl;
		system("pause");
		return -1;
	}
}