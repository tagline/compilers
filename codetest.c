#include <stdio.h>

int test(int b,int c,int a)
{
	
	//int a = 5;
	b = 8+c;
	c= a+b;
	return c;
}

int main()
{
    int firstNumber, secondNumber, sumOfTwoNumbers;
    
    printf("Enter two integers: ");
	 firstNumber = 5;
	secondNumber = 10;
    // Two integers entered by user is stored using scanf() function
    //scanf("%d %d", &firstNumber, &secondNumber);

    // sum of two numbers in stored in variable sumOfTwoNumbers
    sumOfTwoNumbers = firstNumber + secondNumber;

    // Displays sum      
    //printf("%d + %d = %d", firstNumber, secondNumber, sumOfTwoNumbers);

    return 0;
}
