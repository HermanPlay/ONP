#pragma once

#include "Token.h"
#include <iostream>

using namespace std;


class Stack {
private:
	struct ListNode
	{
		Token* value;
		ListNode * next;

		ListNode(Token* value1)
		{
			value = value1;
			next = nullptr;
		}

		~ListNode()
		{
			delete value;
		}
	};
public:
	ListNode * head;
	int count;

	Stack()
	{
		head = nullptr;
		count = 0;
	}

	~Stack()
	{
		while (head != nullptr)
		{
			ListNode * temp = head;
			head = head->next;
			delete temp;
			count--;
		}
	}

	void Push(ListNode* node)
	{
		node->next = head;
		head = node;
		count++;
	}

	void Push(bool isOperator, bool isNumber, bool isLeftParenthesis, int number, int funType, int numOfArgs, int priority)
	{
		Token * temp = new Token(isOperator, isNumber, isLeftParenthesis, number, funType, numOfArgs, priority);
		ListNode * node = new ListNode(temp);
		node->next = head;
		head = node;
		count++;
	}

	ListNode* Pop()
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		ListNode * temp = head;
		head = head->next;
		count--;
		return temp;
	}

	Token* Peek()
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		return head->value;
	}

	bool IsEmpty()
	{
		return count == 0;
	}

	void Print(bool doubleSpace)
	{
		ListNode * temp = head;
		while (temp != nullptr)
		{
			temp->value->Print();
			temp = temp->next;
			if (doubleSpace)
				cout << "  ";
			else 
				cout << " ";
		}
		cout << endl;
	}

	void Reverse()
	{
		ListNode * prev = nullptr;
		ListNode * current = head;
		ListNode * next = nullptr;
		while (current != nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
	}
};