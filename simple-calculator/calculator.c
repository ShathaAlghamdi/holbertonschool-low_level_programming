#include <stdio.h>

int addition(int a, int b) {
    return a + b;
}

int subtraction(int a, int b)
{
    return a - b;
}

int multiplication(int a, int b)
{
    return (a * b);
}

int division(int a, int b)
{
	if (b != 0)
	{
		return (a / b);
	}
	else
	{
		printf("Error: Division by zero is not allowed.\n");
		return (-1);
	}
}

int main(void)
{
	int a, b, menuselection, result;

	menuselection = -1;

	printf("welcome to the simple calculator\n");
	printf(" Simple Calculator \n 1) Add \n 2) Subtract \n 3) Multiply \n 4) Divide \n 0) Quit \n");

	while (menuselection != 0)
	{
		printf("Enter your choice: ");
		scanf("%d", &menuselection);

		if (menuselection == 1)
		{
			printf("Enter two numbers: ");
			scanf("%d %d", &a, &b);
			printf("Sum of %d and %d is %d\n",
				a, b, addition(a, b));
		}
		else if (menuselection == 2)
		{
			printf("Enter two numbers: ");
			scanf("%d %d", &a, &b);
			printf("Difference of %d and %d is %d\n",
				a, b, subtraction(a, b));
		}
		else if (menuselection == 3)
		{
			printf("Enter two numbers: ");
			scanf("%d %d", &a, &b);
			printf("Product of %d and %d is %d\n",
				a, b, multiplication(a, b));
		}
		else if (menuselection == 4)
		{
			printf("Enter two numbers: ");
			scanf("%d %d", &a, &b);

			result = division(a, b);

			if (result != -1)
			{
				printf("Quotient of %d and %d is %d\n",
					a, b, result);
			}
		}
		else if (menuselection == 0)
		{
			printf("Bye!\n");
		}
		else
		{
			printf("Invalid choice\n");
		}
}
return (0);
}
