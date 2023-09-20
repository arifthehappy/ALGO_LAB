#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

struct Point
{
    int x, y;
};

int compareX(const void* a, const void* b)
{
    struct Point* p1 = (struct Point*)a, * p2 = (struct Point*)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
    struct Point* p1 = (struct Point*)a, * p2 = (struct Point*)b;
    return (p1->y - p2->y);
}

float dist(struct Point p1, struct Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(struct Point P[], int n, struct Point* closest1, struct Point* closest2)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float distance = dist(P[i], P[j]);
            if (distance < min)
            {
                min = distance;
                *closest1 = P[i];
                *closest2 = P[j];
            }
        }
    }
    return min;
}

float min(float x, float y)
{
    return (x < y) ? x : y;
}

float stripClosest(struct Point strip[], int size, float d, struct Point* closest1, struct Point* closest2)
{
    float min = d;

    qsort(strip, size, sizeof(struct Point), compareY);

    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
        {
            float distance = dist(strip[i], strip[j]);
            if (distance < min)
            {
                min = distance;
                *closest1 = strip[i];
                *closest2 = strip[j];
            }
        }
    }

    return min;
}

float closestUtil(struct Point P[], int n, struct Point* closest1, struct Point* closest2)
{
    if (n <= 3)
        return bruteForce(P, n, closest1, closest2);

    int mid = n / 2;
    struct Point midPoint = P[mid];

    float dl = closestUtil(P, mid, closest1, closest2);
    float dr = closestUtil(P + mid, n - mid, closest1, closest2);

    float d = min(dl, dr);

    struct Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(P[i].x - midPoint.x) < d)
        {
            strip[j] = P[i];
            j++;
        }
    }

    return min(d, stripClosest(strip, j, d, closest1, closest2));
}

float closest(struct Point P[], int n, struct Point* closest1, struct Point* closest2)
{
    qsort(P, n, sizeof(struct Point), compareX);
    return closestUtil(P, n, closest1, closest2);
}

int main()
{
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);
    printf("\n");

    struct Point arr[n];

    printf("Enter pairs of points:\n");
    for (int i = 0; i < n; i++)
    {
        int tx, ty;
        scanf("%d %d", &tx, &ty);

        arr[i].x = tx;
        arr[i].y = ty;

        printf("\n");
    }

    struct Point closest1, closest2;

    float minDistance = closest(arr, n, &closest1, &closest2);

    printf("The smallest distance is %f\n", minDistance);
    printf("Closest points: (%d, %d) and (%d, %d)\n", closest1.x, closest1.y, closest2.x, closest2.y);

    return 0;
}
