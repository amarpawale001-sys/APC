/*
Name: Amarnath Pawale

Date: 20/06/2026

Project Name: Arbitrary Precision Calculator in C

Description:

This project is a command-line based Arbitrary Precision Calculator developed
using the C programming language. It performs arithmetic operations on integers
of any size by storing individual decimal digits in a doubly linked list.

The calculator provides the following functionalities:
Addition of positive and negative integers
Subtraction of positive and negative integers
Multiplication using the 'x' operator
Integer division using the '/' operator
Validation of operands and operators
Handling of leading zeros and signed values
Detection of division by zero

Usage:
./apc <number1> <operator> <number2>

Some special cases:
./apc -100 + 50
Result: -50

./apc -100 - -50
Result: -50

./apc -12 x -5
Result: 60

./apc -100 / -5
Result: 20

./apc 001000 + 000500
Result: 1500

./apc 001000 / 00025
Result: 40

./apc 999999999999999999 + 1
Result: 1000000000000000000

./apc 999999999999 x 999999999999
Result: 999999999998000000000001

Error cases

./apc 10 % 5
Operator should be +, -, x or /

./apc 100 +
Number2 should contain at least one digit

./apc 12a + 10
Number1 should contain digits only

*/

#include "apc.h"

int main(int argc, char *argv[])
{
   node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;
   int result;
   int sign1 = 1;
   int sign2 = 1;

    // Validation
    if(argc != 4)
	{
	printf("There should be 4 arguments passed\n");
    return FAILURE;
	}

   int i, j;

   for(j = 1; j <= 3; j = j + 2)
   {

    i = 0;
    if(argv[j][0] == '-' || argv[j][0] == '+')
    {
        i++;
    }

    /* Operand should contain at least one digit */
   if(argv[j][i] == '\0')
   {
    if(j == 1)
        printf("Number 1 should contain at least one digit\n");
    else
        printf("Number 2 should contain at least one digit\n");

    return FAILURE;
   }
    while(argv[j][i] != '\0')
    {
       if(!isdigit(argv[j][i]))
    {
       if(j == 1)
        printf("Number 1 should contain digits only\n");
      else
        printf("Number 2 should contain digits only\n");

    return FAILURE;
    }
        i++;
    }
   }

	if(argv[2][0] != '+' &&  argv[2][0] != '-' && argv[2][0] != 'X' && argv[2][0] != 'x' && argv[2][0] != '/' )
	{
		printf("Operator should be +, -, x or /\n");
		return FAILURE;
	}
    
	if(argv[1][0] == '-')
    {
    sign1 = -1;
    }

    if(argv[3][0] == '-')
    {
    sign2 = -1;
    }
    
    // Create 2 lists of operands
	if(create_list(argv[1], &head1, &tail1) == FAILURE)
	{
		return FAILURE;
	}
	if(create_list(argv[3], &head2, &tail2) == FAILURE)
	{
		return FAILURE;
	}

    char oper = argv[2][0];

    switch(oper)
    { 
	case '+':
    if(sign1 == sign2)
    {
        addition(tail1, tail2, &headR, &tailR);

        if(sign1 == -1)
            result = 1;
        else
            result = 0;
    }
   else
   {
    result = subtraction(tail1, tail2, &headR, &tailR);

    if(sign1 == -1 && sign2 == 1)
    {
        result = !result;
    }
   }
    break;

	case '-':
    if(sign1 != sign2)
    {
        addition(tail1, tail2, &headR, &tailR);

        if(sign1 == -1)
            result = 1;
        else
            result = 0;
    }
   else
   {
    if(sign1 == -1 && sign2 == -1)
    {
        result = subtraction(tail2, tail1, &headR, &tailR);
    }
    else
    {
        result = subtraction(tail1, tail2, &headR, &tailR);
    }
    }
    break;
    
    case 'x':
    case 'X':
    multiplication(tail1, tail2, &headR, &tailR);

    if(sign1 != sign2)
        result = 1;
    else
        result = 0;

    break;
	
 case '/':
    if(division(head1, tail1, head2, tail2, &headR, &tailR) == FAILURE)
    {
        printf("Division by zero\n");
        return FAILURE;
    }

    if(sign1 != sign2)
        result = 1;
    else
        result = 0;

    break;

	default:
	    printf("Invalid operator\n");
    }
	if(headR != NULL && headR->data == 0 && headR->next == NULL)
   {
    result = 0;
   }
	printf("Result: ");
    if(result == 1)
    {
    printf("-");
    }
	print_list(headR);
}

