#pragma once

#define NUMBER 0
#define PLUS 3
#define MINUS 4
#define MULTIPLY 5
#define DIVIDE 6
#define NEGATION 7
#define LEFTBRACKET 2
#define COND 8
void print_operator(int type);
class Token
{
public:
	bool isOperator;
	bool isNumber;
	bool isLeftParenthesis;
	int number;
	int funType;
	int numOfArgs;
	int priority;

	Token(bool _isOperator, bool _isNumber, bool _isLeftParenthesis, int _number, int _funType, int _numOfArgs, int _priority)
	{
		isOperator = _isOperator;
		isNumber = _isNumber;
		isLeftParenthesis = _isLeftParenthesis;
		number = _number;
		funType = _funType;
		numOfArgs = _numOfArgs;
		priority = _priority;
	}

	void Print()
	{
		if (isNumber)
		{
			printf("%d", number);
		}
		else if (isLeftParenthesis)
		{
			printf("%c", '(');
		}
		else
		{
			print_operator(funType);
		}
	
	}


};

int get_priority(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case 'N':
		return 4;
	case 'I':
		return 5;
	default:
		return 0;
	}
}

int get_operator_type(char c)
{
	switch (c)
	{
	case '+':
		return PLUS;
	case '-':
		return MINUS;
	case '*':
		return MULTIPLY;
	case '/':
		return DIVIDE;
	default:
		return 0;
	}
}

void print_operator(int type)
{
	switch (type)
	{
	case PLUS:
		printf("%c", '+');
		break;
	case MINUS:
		printf("%c", '-');
		break;
	case MULTIPLY:
		printf("%c", '*');
		break;
	case DIVIDE:
		printf("%c", '/');
		break;
	case NEGATION:
		printf("%c", 'N');
		break;
	case COND:
		printf("%s", "IF");
		break;
	}
}