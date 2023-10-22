#include<stdio.h>
#include <stdlib.h>
#include<limits.h>

int funmax(int a, int b) 
{ return (a > b)? a : b;}

int cutRodDP(int price[], int n)
{

int * val= (int *)malloc(sizeof(int) * (n+1));
val[0] = 0;
int i, j;

for (i = 1; i<=n; i++)
{
	int max_val = INT_MIN;
	for (j = 0; j < i; j++)
    {
		max_val = funmax(max_val, price[j] + val[i-j-1]);
    }
	val[i] = max_val;
}

return val[n];
}

int main()
{
	int size;
    printf("Enter the length of the rod: ");
    scanf("%d", &size);
    printf("Enter the price of each length: ");
    int *price = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &price[i]);
    }

	printf("Maximum Value is %d", cutRodDP(price, size));

	return 0;
}
