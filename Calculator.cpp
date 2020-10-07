#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

void toPos(char *);
int calculate(char *);
int* getNum(char *);
int ALU(int, int, char);

int ALU(int a, int b, char Myoperator)
{
	int result;
	switch (Myoperator)
	{
		case '+':
			return a+b;
			break;
		case '-':
			return a-b;
			break;
		case '*':
			return a*b;
			break;
		case '/':
			return a/b;
			break;
	}
}

int calculate(char *string)
{
	int *num = getNum(string);
	char *posStr;
	int posIndex = 0, numIndex = 0, strIndex = 0;
	int x = 0, result = 0;
	
	posStr = string;
	toPos(posStr);
	
	while(posStr[posIndex] != '\0')
	{
		if((posStr[posIndex] < '0') || (posStr[posIndex] > '9'))
		{
			num[posStr[posIndex-2]-48] = ALU(num[posStr[posIndex-2]-48], num[posStr[posIndex-1]-48], posStr[posIndex]);
			x = posIndex - 1;
			while(posStr[x] != '\0')
			{
				posStr[x] = posStr[x+2];
				x++;
			}
			posIndex-=2;
		}
		posIndex++;
	}
	
	result = *num;
	delete []num;
	
	return result;
}

int* getNum(char string[100])
{
	int *a, numIndex = 0, strIndex = 0;
	a = (int *)malloc(sizeof(int)*20);
	memset(a, 0, sizeof(int)*20);
	
	while(string[strIndex] != '\0')
	{
		if((string[strIndex] < '0') || (string[strIndex] > '9'))
			numIndex++;
		else
		{
			*(a+numIndex) *= 10;
			*(a+numIndex) += string[strIndex]-48;
		}
		strIndex++;
	}
	return a;
}

void toPos(char *string)
{
	char tempStr[100];
	int x = 0, top = -1, numCount = 0, strCount = 0;
	char stack[100];
	bool popFlag = false;
	
	strcpy(tempStr, string);
	while(tempStr[x] != '\0')
	{
		if((tempStr[x] == '+') || (tempStr[x] == '-') || (tempStr[x] == '*') || (tempStr[x] == '/'))
		{
			string[strCount] = numCount + 48;
			numCount++;
			strCount++;
			if(popFlag == true && (tempStr[x] == '+' || tempStr[x] == '-'))
			{
				while(top > -1)
				{
					string[strCount] = stack[top];
					strCount++;
					top--;
				} 
				popFlag = false;
			}
			if(((tempStr[x] == '*') || (tempStr[x] == '/')))
			{
				if(((stack[top] == '*') || (stack[top] == '/')))
				{
					string[strCount] = stack[top];
					strCount++;
					stack[top] = tempStr[x];	
				}
				else
				{
					top++;
					stack[top] = tempStr[x];
				}
				popFlag = true;
			}
			else if(((tempStr[x] == '+') || (tempStr[x] == '-')) && top != -1)
			{
				string[strCount] = stack[top];
				strCount++;
				stack[top] = tempStr[x];
			}
			else	//如果是加或減，且stack內沒有值，就直接把這個存進去 
			{
				top++;
				stack[top] = tempStr[x];
			}
		}
		x++;
	}
	string[strCount] = numCount + 48;
	strCount++;
	while(top >= -1)
	{
		string[strCount] = stack[top];
		strCount++;
		top--;
	} 
	string[strCount] = '\0';
}



int main()
{
	//char equation[100] = "12+3*9-9";
	int *a, result = 0;
	char equation[100] = "12*9";
	while(1)
	{
		printf("\nPlease enter the equation: ");
		scanf("%s",equation);
		result = calculate(equation);
		printf("\nThe answer is: %d",result);
	}
	
	return 0;
 } 
