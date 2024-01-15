#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

// Structure pour représenter un nœud de l'arbre binaire de recherche
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Fonction pour créer un nouveau nœud avec une valeur donnée
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Fonction pour insérer une valeur dans l'arbre
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Fonction pour rechercher une valeur dans l'arbre
Node* search(Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    }

    return search(root->right, value);
}

// Fonction pour trouver le nœud avec la valeur minimale dans un sous-arbre
Node* minValueNode(Node* node) {
    Node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Fonction pour supprimer un nœud avec une valeur donnée de l'arbre
Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

int main() {
    // Initialisation de la fenêtre Raylib
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Arbre Binaire de Recherche");

    // Racine de l'arbre
    Node* root = NULL;

    // Boucle principale
    while (!WindowShouldClose()) {
        // Code ici pour gérer l'interface utilisateur, la saisie des valeurs, etc.

        // Exemple d'utilisation : insérer, rechercher et supprimer des valeurs
        root = insert(root, 50);
        root = insert(root, 30);
        root = insert(root, 20);
        root = insert(root, 40);
        root = insert(root, 70);
        root = insert(root, 60);
        root = insert(root, 80);

        Node* searchResult = search(root, 40);
        if (searchResult != NULL) {
            printf("La valeur 40 a été trouvée dans l'arbre.\n");
        } else {
            printf("La valeur 40 n'a pas été trouvée dans l'arbre.\n");
        }

        root = deleteNode(root, 30);
    }

    // Nettoyage des ressources
    CloseWindow();

    return 0;
}
