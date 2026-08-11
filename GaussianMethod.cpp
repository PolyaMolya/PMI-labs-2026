#define EPS 1e-13
#include "Vector.h"
#include "SLU.h"
#include <stdio.h>
#include "Exceptions.h"
#include <iostream>

void ClearBuffer()
{
	int c;
	while ((c = getchar()) != '\n');
}

typedef double type;
const type epsilon = EPS;

int main()
{
	unsigned int n;

	do
	{
		printf("Enter size of square matrix (positive integer):\n");
		scanf("%u", &n);
		ClearBuffer();
	} while (n <= 0);

	SLU<type> Sys(n);

	printf("Fill this matrix with numbers:\n");
	Sys.InputMatrix();
	ClearBuffer();

	char choice;
	do
	{
		Vector<type> right(n);

		printf("Enter the coordinates of the vector of the right part of the system:\n");
		right.InputVector();
		ClearBuffer();

		printf("The system introduced:\n\n");
		Sys.PrintSLU(right);

		printf("Answer:\n\n");

		try
		{
			Sys.GaussMethod(right, epsilon);
		}
		catch (const Exception& e)
		{
			switch (e.kod)
			{
			case 1: std::cout << e.message << '\n'; break;
			case 2: std::cout << e.message << '\n'; break;
			case 3: std::cout << e.message << '\n'; break;
			case 4: std::cout << e.message << '\n'; break;
			}
		}
		do
		{
			printf("Do you want to continue working with this coefficient matrix? (Y/n) \n");
			scanf("%c", &choice, sizeof(choice));
			ClearBuffer();
		} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
	} while (choice == 'Y' || choice == 'y');
	return 0;
}