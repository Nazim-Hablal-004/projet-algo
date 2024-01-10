#include "raylib.h"
#include <stddef.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Fonction pour créer un nouveau nœud
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour insérer un nouveau nœud dans l'arbre
TreeNode* insert(TreeNode* root, int value) {
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

// Fonction pour dessiner un nœud et ses sous-arbres
void drawTreeNode(TreeNode* root, int x, int y, int horizontalSpacing) {
    if (root != NULL) {
        // Dessine le nœud
        DrawText(TextFormat("%d", root->value), x, y, 20, BLACK);

        // Dessine les liens vers les enfants
        if (root->left != NULL) {
            DrawLine(x + 10, y + 20, x - horizontalSpacing + 10, y + 60, BLACK);
            drawTreeNode(root->left, x - horizontalSpacing, y + 40, horizontalSpacing / 2);
        }
        if (root->right != NULL) {
            DrawLine(x + 10, y + 20, x + horizontalSpacing + 10, y + 60, BLACK);
            drawTreeNode(root->right, x + horizontalSpacing, y + 40, horizontalSpacing / 2);
        }
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Initialisation de Raylib
    InitWindow(screenWidth, screenHeight, "Binary Tree with Raylib");
    SetTargetFPS(60);

    TreeNode* root = NULL;

    // Insertion de quelques valeurs dans l'arbre
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dessin de l'arbre binaire
        if (root != NULL) {
            drawTreeNode(root, screenWidth / 2, 40, screenWidth / 4);
        }

        EndDrawing();
    }

    // Libération de la mémoire utilisée par l'arbre (optionnel)
    // Vous pouvez créer une fonction pour libérer récursivement la mémoire de l'arbre

    CloseWindow();

    return 0;
}
