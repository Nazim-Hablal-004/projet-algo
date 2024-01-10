#include "raylib.h"
#include <stddef.h>

typedef struct TreeNode {
    double value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Fonction pour créer un nouveau nœud
TreeNode* createNode(double value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour insérer un nouveau nœud dans l'arbre
TreeNode* insert(TreeNode* root, double value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Fonction pour libérer la mémoire utilisée par l'arbre
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Fonction pour dessiner un nœud et ses sous-arbres
void drawTree(TreeNode* root, int x, int y, int horizontalSpacing) {
    if (root != NULL) {
        // Dessine le nœud
        DrawText(TextFormat("%lf", root->value), x, y, 20, BLACK);

        // Dessine les liens vers les enfants
        if (root->left != NULL) {
            DrawLine(x + 10, y + 20, x - horizontalSpacing + 10, y + 60, BLACK);
            drawTree(root->left, x - horizontalSpacing, y + 40, horizontalSpacing / 2);
        }
        if (root->right != NULL) {
            DrawLine(x + 10, y + 20, x + horizontalSpacing + 10, y + 60, BLACK);
            drawTree(root->right, x + horizontalSpacing, y + 40, horizontalSpacing / 2);
        }
    }
}



int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Initialisation de Raylib
    InitWindow(screenWidth, screenHeight, "Arbre Binaire en utilisant Raylib");
    SetTargetFPS(60);

    TreeNode* root = NULL;
    double T[100];
    int N;
    


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // entrer le nombre de nœuds et leurs valeurs
          DrawText("donnez le nombre des noeuds : ", 10, 10, 20, BLACK);

    // Demander à l'utilisateur de saisir le nombre de nœuds
    scanf("%d", &N);

    // Demander à l'utilisateur de saisir les valeurs des nœuds
    for (int i = 0; i < N; i++) {
        DrawText(TextFormat("Entrez la valeur du noeud %d :", i + 1), 10, 40 + i * 30, 20, BLACK);
        scanf("%lf", &T[i]);
    }
        
        // Insérer les valeurs dans l'arbre
        for(int i= 0;  i<N; i++){
        root = insert(root, T[i]);
        
        // Dessiner l'arbre binaire
        drawTree(root, screenWidth / 2, 40, screenWidth / 4);
        }
        EndDrawing();
    }

    // Libération de la mémoire utilisée par l'arbre
    freeTree(root);

    CloseWindow();

    return 0;
}