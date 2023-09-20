

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point{
    int x;
    int y;
};

double distance(struct point A, struct point B){
    double distance;
    distance = sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2));
    return distance;
}

int main(){
    double min = __INT_MAX__;
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);
    printf( "\n");

    struct point arr[n];

    printf("enter  pairs of point\n");
    for(int i =0; i <n ;i++){
        int tx,ty;
        scanf("%d", &tx);
        scanf("%d", &ty);

        arr[i].x = tx;
        arr[i].y = ty;

        printf("\n");

    }

    int mini, miny;

    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j <n; j++){
            double d = distance(arr[i], arr[j]);
            if(d < min){
                min = d;
                mini = i;
                miny = j;
            }
        }
    }
printf ( "\n");
    printf("min distance : %lf", min);
    printf("\npoint A: %d, %d", arr[mini].x, arr[mini].y);
    printf("\npoint B: %d, %d", arr[miny].x, arr[miny].y);
    printf ( "\n");
}