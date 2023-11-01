#include <stdio.h>
#include <stdlib.h>

#define NMAX 20

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

int C[NMAX][NMAX]; // cost matrix
int W[NMAX][NMAX]; // weight matrix
int R[NMAX][NMAX]; // root matrix
int q[NMAX];       // unsuccessful searches
int p[NMAX];       // frequencies
int NUMBER_OF_KEYS; // number of keys in the tree
int KEYS[NMAX];
Node *ROOT;

void COMPUTE_W_C_R(FILE *file) {
    int i, j, k, h, m, x, min;

    // Construct weight matrix W
    for (i = 0; i <= NUMBER_OF_KEYS; i++) {
        W[i][i] = q[i];
        for (j = i + 1; j <= NUMBER_OF_KEYS; j++)
            W[i][j] = W[i][j - 1] + p[j] + q[j];
    }

    // Construct cost matrix C and root matrix R
    for (i = 0; i <= NUMBER_OF_KEYS; i++) {
        C[i][i] = W[i][i];
    }

    for (i = 0; i <= NUMBER_OF_KEYS - 1; i++) {
        j = i + 1;
        C[i][j] = C[i][i] + C[j][j] + W[i][j];
        R[i][j] = j;
    }

    for (h = 2; h <= NUMBER_OF_KEYS; h++) {
        for (i = 0; i <= NUMBER_OF_KEYS - h; i++) {
            j = i + h;
            m = R[i][j - 1];
            min = C[i][m - 1] + C[m][j];

            for (k = m + 1; k <= R[i + 1][j]; k++) {
                x = C[i][k - 1] + C[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }

            C[i][j] = W[i][j] + min;
            R[i][j] = m;
        }
    }

    // Display weight matrix W, cost matrix C, root matrix R, and optimal cost
    printf("\nThe weight matrix W:\n");
    for (i = 0; i <= NUMBER_OF_KEYS; i++) {
        for (j = i; j <= NUMBER_OF_KEYS; j++)
            printf("%d ", W[i][j]);
        printf("\n");
    }

    printf("\nThe cost matrix C:\n");
    for (i = 0; i <= NUMBER_OF_KEYS; i++) {
        for (j = i; j <= NUMBER_OF_KEYS; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    printf("\nThe root matrix R:\n");
    for (i = 0; i <= NUMBER_OF_KEYS; i++) {
        for (j = i; j <= NUMBER_OF_KEYS; j++)
            printf("%d ", R[i][j]);
        printf("\n");
    }

    printf("\nThe cost of the optimal binary search tree is: %d\n", C[0][NUMBER_OF_KEYS]);
}

// Construct the optimal binary search tree
Node *CONSTRUCT_OBST(int i, int j) {
    if (i > j)
        return NULL;

    Node *p = (Node *)calloc(1, sizeof(Node));
    int rootIndex = R[i][j];
    p->key = KEYS[rootIndex];
    p->left = CONSTRUCT_OBST(i, rootIndex - 1); // left subtree
    p->right = CONSTRUCT_OBST(rootIndex, j);    // right subtree

    return p;
}

// Display the optimal binary search tree
void DISPLAY(Node *ROOT, int space) {
    if (ROOT == NULL)
        return;

    space += 3;
    DISPLAY(ROOT->right, space);

    printf("\n");
    for (int i = 3; i < space; i++)
        printf(" ");
    printf("%d\n", ROOT->key);

    DISPLAY(ROOT->left, space);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fscanf(file, "%d", &NUMBER_OF_KEYS);
    for (int i = 1; i <= NUMBER_OF_KEYS; i++)
        fscanf(file, "%d", &KEYS[i]);

    for (int i = 1; i <= NUMBER_OF_KEYS; i++)
        fscanf(file, "%d", &p[i]);

    for (int i = 0; i <= NUMBER_OF_KEYS; i++)
        fscanf(file, "%d", &q[i]);

    COMPUTE_W_C_R(file);

    // Construct the optimal binary search tree
    ROOT = CONSTRUCT_OBST(0, NUMBER_OF_KEYS);

    // Display the optimal binary search tree
    printf("\nOptimal Binary Search Tree Structure:\n");
    DISPLAY(ROOT, 0);

    fclose(file);

    return 0;
}
