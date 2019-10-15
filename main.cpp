#include <iostream>
#include <string>

struct stack
{
    double num;
    char sign;
} r[1000]; //stack of numbers & operations
stack pol[1000]; //stack of pol notation 
int lr = 0;


int isCharIsNum(char c)
{
	if (c-48 >= 0 && c-48 <= 9)
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

std::string get_num(std::string s)
{
    std::string res ="";
    //int lr = 0;

    double c = 0;
    int cnum = 0;
    double unarminus = 1; 
    double point = 0;
	for(int i=0; i<size(s); i++)
    {
         
        if (isCharIsNum (s[i])) 
        {
            cnum = 1;
            if (point>5) 
            {
                c += (s[i]-48)/point;
                point *= 10;
            }
            else
                c = c*10 + s[i]-48;
        } else
        if (s[i] == '.' || s[i] ==',')
        {
            if(cnum && point<5) point = 10;
            else
            {
                res = "ERROR wrong .";
                break;            
            } 
        } else
        if (isCharIsSign (s[i])) 
        {
            point = 0;
            if(cnum) 
            {
                r[lr].num = c*unarminus;
                r[lr].sign = '1';
                lr++;
                c = 0;
                cnum = 0;
                unarminus = 1;
            } else
            if(s[i] == '-')
            {
                unarminus = -1;
            } else
            {
                res = "ERROR wrong operations";
                break;
            }
            
            
            if (unarminus != -1)
            {
                r[lr].sign = s[i];
                lr++;
            }
        } else
        if (s[i] == ' ')
        {
            point = 0;
            if(cnum) 
            {
                r[lr].num = c*unarminus;
                r[lr].sign = '1';
                lr++;
                c = 0;
                cnum = 0;
                unarminus = 1;
            }
        } else
        {
            res = "ERROR wrong symbols";
            break;
        }
    }

        if(cnum) 
        {
            r[lr].num = c*unarminus;
            r[lr].sign = '1';
            
        }

    return res;
}

void trans()
{
    stack teh[2];
    int lteh = -1;
    int lp = 0;
    pol[lp].num = r[0].num;
    pol[lp].sign = r[0].sign;

    for (int i=1; i <= lr; i++)
    {
        switch (r[i].sign)
        {
        case '+':
        case '-':
            if (lteh == -1)
            {
                lteh ++;
                teh[lteh].sign=r[i].sign;
                teh[lteh].num=r[i].num;
                
            } else
            if (teh[lteh].sign == '+' || teh[lteh].sign == '-')
            {
                lp++;
                pol[lp].sign=teh[lteh].sign;
                pol[lp].num=teh[lteh].num;

                teh[lteh].sign=r[i].sign;
                teh[lteh].num=r[i].num;
                
            } else
            if (teh[lteh].sign == '*' || teh[lteh].sign == '/')
            {
                lp++;
                pol[lp].sign=teh[lteh].sign;
                pol[lp].num=teh[lteh].num;   
                lteh --;
                if (lteh > -1)
                {
                    lp++;
                    pol[lp].sign=teh[lteh].sign;
                    pol[lp].num=teh[lteh].num;   
                    lteh --;
                    
                }
                lteh ++;
                teh[lteh].sign=r[i].sign;
                teh[lteh].num=r[i].num;
                            
            }
            break;

        case '1':
            
            lp++;
            pol[lp].sign=r[i].sign;
            pol[lp].num=r[i].num;
            if(i == lr)
            {
                while(lteh > -1)
                {
                    lp++;
                    pol[lp].sign=teh[lteh].sign;
                    pol[lp].num=teh[lteh].num;
                    lteh--;
                }
            } 
            break;
        case '/':
        case '*':

            if (lteh == -1 || teh[lteh].sign == '+' || teh[lteh].sign == '-')
            {
                lteh ++;
                teh[lteh].sign=r[i].sign;
                teh[lteh].num=r[i].num;
                
            } else
            
            if (teh[lteh].sign == '*' || teh[lteh].sign == '/')
            {
                lp++;
                pol[lp].sign=teh[lteh].sign;
                pol[lp].num=teh[lteh].num;

                teh[lteh].sign=r[i].sign;
                teh[lteh].num=r[i].num;
                            
            }
            break;

    
        }

    }
}


double calc()
{
    stack st[1000];
    int lst = 0;
    st[lst].sign=pol[0].sign;
    st[lst].num=pol[0].num;

    for(int i=1; i<=lr; i++)
    {
        
        if (pol[i].sign == '1')
        {
            lst++;
            st[lst].sign=pol[i].sign;
            st[lst].num=pol[i].num;
            
        }else
        {
            lst--;
            st[lst].sign='1';
            switch (pol[i].sign)
            {
            case '+':
                st[lst].num=st[lst].num+st[lst+1].num;
                break;
            case '-':
                st[lst].num=st[lst].num-st[lst+1].num;
                break;
            case '*':
                st[lst].num=st[lst].num*st[lst+1].num;
                break;
            case '/':
                st[lst].num=st[lst].num/st[lst+1].num;
                break;
            }
            
        }
        
    }
    return st[0].num;
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

    //error code
    std::string error = "";

    //check calc word
    if(calc_command != "calc")
    {
        error ="ERROR need calc + ' '";
    }

    //create stack of operations
    if (error =="")
    std::string error = get_num(pr); 

    if (error =="")
    {
        //translate to reverse polish notation
        trans();

        //calculate and print result
        std::cout << calc() << std::endl;
        system("pause");
        return 0;

    } else
    {
        //error output
        std::cout << error << std::endl;
        system("pause");
        return -1;     
    }

}