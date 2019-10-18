#include <iostream>
#include <string>

struct stack
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

stack get_num(const std::string &s,stack* r)
{
	stack res;
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
						r[lr].num = c * unarminus;
						r[lr].sign = '1';
						lr++;
						
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
						r[lr].sign = s[i];
						lr++;
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
		r[lr].num = c * unarminus;
		r[lr].sign = '1';

	}
	res.num = lr;
	return res;
}

void trans(stack* r, int lr)
{
	stack teh[2];
	int lteh = -1;
	int lp = 0;

	for (int i = 1; i <= lr; i++)
	{
		switch (r[i].sign)
		{
		case '+':
		case '-':
			if (lteh == -1)
			{
				lteh++;
				teh[lteh].sign = r[i].sign;
				teh[lteh].num = r[i].num;
			}
			else
				if (teh[lteh].sign == '+' || teh[lteh].sign == '-')
				{
					lp++;
					r[lp].sign = teh[lteh].sign;
					r[lp].num = teh[lteh].num;

					teh[lteh].sign = r[i].sign;
					teh[lteh].num = r[i].num;
				}
				else
					if (teh[lteh].sign == '*' || teh[lteh].sign == '/')
					{
						lp++;
						r[lp].sign = teh[lteh].sign;
						r[lp].num = teh[lteh].num;
						lteh--;
						if (lteh > -1)
						{
							lp++;
							r[lp].sign = teh[lteh].sign;
							r[lp].num = teh[lteh].num;
							lteh--;
						}
						lteh++;
						teh[lteh].sign = r[i].sign;
						teh[lteh].num = r[i].num;
					}
			break;

		case '1':
			lp++;
			r[lp].sign = r[i].sign;
			r[lp].num = r[i].num;
			if (i == lr)
			{
				while (lteh > -1)
				{
					lp++;
					r[lp].sign = teh[lteh].sign;
					r[lp].num = teh[lteh].num;
					lteh--;
				}
			}
			break;

		case '/':
		case '*':
			if (lteh == -1 || teh[lteh].sign == '+' || teh[lteh].sign == '-')
			{
				lteh++;
				teh[lteh].sign = r[i].sign;
				teh[lteh].num = r[i].num;

			}
			else
				if (teh[lteh].sign == '*' || teh[lteh].sign == '/')
				{
					lp++;
					r[lp].sign = teh[lteh].sign;
					r[lp].num = teh[lteh].num;

					teh[lteh].sign = r[i].sign;
					teh[lteh].num = r[i].num;
				}
			break;
		}
	}
}

double calc(stack* pol,int lr)
{	

	stack st[1000];
	int lst = 0;
	st[lst].sign = pol[0].sign;
	st[lst].num = pol[0].num;

	for (int i = 1; i <= lr; i++)
	{

		if (pol[i].sign == '1')
		{
			lst++;
			st[lst].sign = pol[i].sign;
			st[lst].num = pol[i].num;
		}
		else
		{
			lst--;
			st[lst].sign = '1';
			switch (pol[i].sign)
			{
			case '+':
				st[lst].num = st[lst].num + st[lst + 1].num;
				break;
			case '-':
				st[lst].num = st[lst].num - st[lst + 1].num;
				break;
			case '*':
				st[lst].num = st[lst].num*st[lst + 1].num;
				break;
			case '/':
				st[lst].num = st[lst].num / st[lst + 1].num;
				break;
			}
		}
	}
	return st[0].num;
}

stack get_res(const std::string &pr) {

	//create stack of operations	
	stack* r = (stack*) malloc(size(pr)*sizeof(stack));
	stack res;
	stack error = get_num(pr,r);
	int lr = error.num;
	
	if (error.sign == '0')
	{
		//translate to reverse polish notation
		trans(r,lr);
		//calc res
		res.sign = '0';
		res.num = calc(r, lr);
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
	stack res;

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