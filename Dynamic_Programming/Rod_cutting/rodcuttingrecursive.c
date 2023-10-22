// rod cutting problem recursive

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


int cutRodRecursive(int n, int *price )
{
    if(n<=0)
    {
        return 0;
    }

    int maximum = INT_MIN;

    for(int i = 1, x= 0 ; i <= n;x++, i++)
    {
        maximum = fmax(maximum, price[x] + cutRodRecursive(n-i, price));
       
    }

    return maximum;

}

int main()
{
    int n;
    printf("Enter the length of the rod: ");
    scanf("%d", &n);
    printf("Enter the price of each length: ");
    int *price = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &price[i]);
    }


   int maxRecursive = cutRodRecursive(n, price);
   printf("Maximum value is %d\n", maxRecursive);
    return 0;




}

