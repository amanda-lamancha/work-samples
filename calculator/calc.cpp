/*Amanda Ditmore
CS110C
3-20-2017*/

//ASSUMPTION: the user of this program will enter a valid arithmatic string, with no spaces. 
//All numbers will be single digit integers.
//All operations will be +,-,/, or *
//NOTE: many expressions with division will yeild unexpected results due to int division.

#include "stack.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	//part 1: convert from infix to postfix

	string inputString;
	string postfixString;
	Stack<char> inStack;

	cout << "Enter Arithmatic expression: ";
	cin >> inputString;

	char c;
	for( int i = 0; i < inputString.length(); i++)
	{
		c = inputString[i];
		/*/
		//testing:
		cout << "postfix exp: " << postfixString << endl;
		if (!inStack.isEmpty())
			cout << "top of stack: " << inStack.peek() << endl;
		else
			cout << "stack is empty" << endl;
		//*/

		// c is operand, append to postfix expression
		if( c <= '9' && c >= '0' )
		{	
			postfixString+=c;
		}

		// c is '(', push to stack
		else if( c == '(')
		{
			inStack.push(c);
		}

		// c is low precedence operator, remove operators from the stack to the postfix string 
        // until stack empty or '(' reached, then push c to stack.
		else if( c == '+' || c == '-' )
		{
			if(inStack.isEmpty())
			{	
				inStack.push(c);	
			}
			else
			{
				while(!inStack.isEmpty() && inStack.peek() != '(')
				{
					postfixString+=inStack.peek();
					inStack.pop();
				}
				inStack.push(c);
			}
		}
	
		//if c is a high precedence operator, remove high precedence operators from the stack to 
        //the postfix string, until stack empty or '(' reached, then push c to stack.
		else if( c == '/' || c == '*' )
		{
			if(inStack.isEmpty())
			{
				inStack.push(c);
			}
			else
			{

                char temp;
				bool again = true;
				while (!inStack.isEmpty() && again)
				{
					temp = inStack.peek();
					if(temp == '/' || temp == '*')
					{
						postfixString+=temp;
						inStack.pop();
					}
					else
					{
						inStack.push(c);
						again = false;
					}										
				}
			}
		}
        //if c is a ')' remove items from stack and add to string till we reach a '('
		else if( c == ')')
		{
			while( inStack.peek() != '(' )
			{

				postfixString+=inStack.peek();
				inStack.pop();
			}
			inStack.pop();
		}
	}
	//after end of string, pop stack operators off and append to postFix string
	while(!inStack.isEmpty())
	{
		postfixString+=inStack.peek();
		inStack.pop();
	}
				
	
	//testing: 
	//cout << "check string: " << postfixString << endl;

	//part 2: compute result from postfix expression

	Stack<int> numStack;
	int num1, num2, result;
	
	for(int i = 0; i < postfixString.length(); i++)
	{
		c = postfixString[i];
		/*/
        //testing:
		cout << "char: " << c << " top of stack: ";
		numStack.isEmpty()? cout << "empty" :cout << numStack.peek(); 
		cout << endl;
		//*/
		
        //if its a number, push to the stack
		if(c >= '0' && c <= '9')
		{
			numStack.push((int)c - (int)'0');
		}
		
        //if its an operator, pull the top two numbers from the stack and compute
		else
		{
			num2 = numStack.peek();
			numStack.pop();
			num1 = numStack.peek();
			numStack.pop();

			switch (c)
			{
				case '+':
					result = num1 + num2;
					break;
				case '-':
					result = num1 - num2;
					break;
				case '*':
					result = num1 * num2;
					break;
				case '/':

					result = num1 / num2; 
					break;
				
			}
            //result goes back on the stack
			numStack.push(result);
		}
	}
	cout << "Result: " << numStack.peek() << endl;			

}
