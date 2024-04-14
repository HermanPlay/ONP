#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctype.h>
#include "Stack.h"

using namespace std;

int main()
{
    int n;
    cin >> n;
    getchar();
    for (int j = 0; j < n; j++)
    {
        cout << endl;
        Stack stack = Stack();
        Stack onp = Stack();
        int input = getchar();
        while (input)
        {
            if (input == ' ')
            {
                input = getchar();
                continue;
            }
            if (input == ',')
            {
                while (!stack.IsEmpty() && stack.Peek()->funType != LEFTBRACKET)
                {
                    onp.Push(stack.Pop());
                }
            }
            else if (input == '.')
            {
                input = getchar(); // get new line
                break;
            }
            else if (isdigit(input))
            {
                char* str = new char[11];
                int i = 0;
                while (isdigit(input))
                {
                    str[i] = input;
                    input = getchar();
                    i++;
                }
                str[i] = '\0';
                onp.Push(false, true, false, atoi(str), NUMBER, -1, 0);
                delete[] str;

            }
            else if (input == '(')
            {
                stack.Push(false, false, true, 0, LEFTBRACKET, 0, 0);
            }
            else if (input == ')')
            {
                while (!stack.Peek()->isLeftParenthesis)
                {
                    onp.Push(stack.Pop());
                }
                stack.Pop();
            }
            else if (input == '+' || input == '-' || input == '*' || input == '/')
            {
                int priority = get_priority(input);
                while (!stack.IsEmpty() && stack.Peek()->priority >= priority)
                {
                    onp.Push(stack.Pop());
                }
                int opType = get_operator_type(input);
                stack.Push(true, false, false, 0, opType, 2, priority);
            }
            else if (input == 'N')
            {
                int priority = get_priority(input);
                while (!stack.IsEmpty() && stack.Peek()->priority > priority)
                {
                    onp.Push(stack.Pop());
                }
                stack.Push(true, false, false, 0, NEGATION, 1, priority);

            }
            else if (input == 'I')
            {
                getchar(); // GET F
                int priority = get_priority(input);
                while (!stack.IsEmpty() && stack.Peek()->priority >= priority)
				{
					onp.Push(stack.Pop());
				}
                stack.Push(true, false, false, 0, COND, 3, priority);
            }
            //stack.Print(false);
            input = getchar();
        }
        while (!stack.IsEmpty())
        {
            onp.Push(stack.Pop());
        }
        // Print
        onp.Reverse();
        onp.Print(true);
        // Calculations
        bool error = false;
        while (!onp.IsEmpty())
        {
            if (onp.Peek()->isNumber)
            {
                stack.Push(onp.Pop());
            }
            else
            {
                int opertype = onp.Pop()->value->funType;
                print_operator(opertype);
                cout << " ";
                stack.Print(false);
                if (opertype == PLUS)
                {
                    int a = stack.Pop()->value->number;
                    int b = stack.Pop()->value->number;
                    stack.Push(false, true, false, a + b, NUMBER, -1, 0);
                }
                else if (opertype == MINUS)
                {
                    int a = stack.Pop()->value->number;
                    int b = stack.Pop()->value->number;
                    stack.Push(false, true, false, b - a, NUMBER, -1, 0);
                }
                else if (opertype == MULTIPLY)
                {
                    int a = stack.Pop()->value->number;
                    int b = stack.Pop()->value->number;
                    stack.Push(false, true, false, a * b, NUMBER, -1, 0);
                }
                else if (opertype == DIVIDE)
                {
                    int a = stack.Pop()->value->number;
                    int b = stack.Pop()->value->number;
                    if (a == 0)
                    {
                        cout << "ERROR " << endl;
                        error = true;
                        break;
                    }
                    stack.Push(false, true, false, b / a, NUMBER, -1, 0);
                }
                else if (opertype == NEGATION)
                {
                    int a = stack.Pop()->value->number;
                    stack.Push(false, true, false, -a, NUMBER, -1, 0);

                }
                else if (opertype == COND)
                {
                    int c = stack.Pop()->value->number;
                    int b = stack.Pop()->value->number;
                    int a = stack.Pop()->value->number;
                    if (a > 0)
					{
						stack.Push(false, true, false, b, NUMBER, -1, 0);
					}
					else
					{
						stack.Push(false, true, false, c, NUMBER, -1, 0);
					}
                }
            }
        }
        if (!error && stack.Peek()->isNumber)
        {
            cout << stack.Pop()->value->number << " " << endl;
        }
    }
    return 0;
}
