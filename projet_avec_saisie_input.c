#include "raylib.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode {
    double value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(double value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

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

void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void drawTree(TreeNode* root, int x, int y, int horizontalSpacing) {
    if (root != NULL) {
        DrawText(TextFormat("%lf", root->value), x, y, 20, BLACK);

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

    InitWindow(screenWidth, screenHeight, "Arbre Binaire en utilisant Raylib");
    SetTargetFPS(60);

    TreeNode* root = NULL;
    double value;

    // Variables pour la boîte de saisie de texte
    char inputValue[64] = ""; // Pour stocker la valeur saisie
    bool inputActive = false; // Pour indiquer si la boîte de saisie est active

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Afficher les instructions
        DrawText("Entrez la valeur du noeud (0 pour terminer) :", 10, 10, 20, BLACK);

        // Afficher la boîte de saisie de texte
        DrawText(inputValue, 10, 40, 20, BLACK);

        // Gérer l'entrée de texte
        if (!inputActive) {
            // Activer la boîte de saisie
            inputActive = TextInputBox((Rectangle){10, 40, 200, 30}, inputValue, 64, true);
        } else {
            // Terminer la saisie si la touche "Entrée" est pressée
            if (IsKeyPressed(KEY_ENTER)) {
                if (strcmp(inputValue, "0") == 0) {
                    // Terminer la saisie si la valeur est 0
                    inputActive = false;
                } else {
                    // Convertir la chaîne en double
                    value = atof(inputValue);
                    root = insert(root, value);
                    // Effacer la boîte de saisie après chaque entrée
                    strcpy(inputValue, "");
                }
            }
        }

        // Dessiner l'arbre binaire
        drawTree(root, screenWidth / 2, 40, screenWidth / 4);

        EndDrawing();
    }

    // Libération de la mémoire utilisée par l'arbre
    freeTree(root);

    CloseWindow();

    return 0;
}
