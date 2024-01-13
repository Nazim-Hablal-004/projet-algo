#include <raylib.h>
#include <stdlib.h>

#define MAX_INPUT_CHARS 20
#define RADIUS 25

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Rectangle rect;
    Color color;
    bool pressed;
} Button;

typedef struct {
    Rectangle textBox;
    Color color;
    bool mouseOn;
    char text[MAX_INPUT_CHARS + 1];
} TextField;

Node *root = NULL;

int ArbreVide(Node *node) {
    return (node == NULL);
}

Node *creerNoeud(int valeur) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = valeur;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void inserer(Node **node, int valeur) {
    if (*node == NULL) {
        *node = creerNoeud(valeur);
    } else {
        if (valeur < (*node)->data) {
            inserer(&(*node)->left, valeur);
        } else if (valeur > (*node)->data) {
            inserer(&(*node)->right, valeur);
        }
    }
}

Node *rechercher(Node *node, int valeur) {
    if (node == NULL || node->data == valeur) {
        return node;
    }

    if (valeur < node->data) {
        return rechercher(node->left, valeur);
    }

    return rechercher(node->right, valeur);
}

Node *supprimer(Node *root, int valeur) {
    if (root == NULL) {
        return root;
    }

    if (valeur < root->data) {
        root->left = supprimer(root->left, valeur);
    } else if (valeur > root->data) {
        root->right = supprimer(root->right, valeur);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = supprimer(root->right, temp->data);
    }
    return root;
}

void drawNode(Node *node, float x, float y, float spacing) {
    if (node != NULL) {
        // Dessiner le cercle du nœud
        DrawCircle(x, y, RADIUS, WHITE);
        DrawText(TextFormat("%d", node->data), (int)x - 10, (int)y - 10, 20, BLACK);

        // Dessiner les branches gauche et droite
        if (node->left != NULL) {
            DrawLine(x, y, x - spacing, y + 80, BLACK);
            drawNode(node->left, x - spacing, y + 80, spacing / 2);
        }
        if (node->right != NULL) {
            DrawLine(x, y, x + spacing, y + 80, BLACK);
            drawNode(node->right, x + spacing, y + 80, spacing / 2);
        }
    }
}

void drawButtons(TextField *textField, Button *button, const char *buttonText) {
    // Dessiner la zone de texte
    DrawRectangleRec(textField->textBox, textField->color);
    DrawRectangleLines(textField->textBox.x, textField->textBox.y, textField->textBox.width, textField->textBox.height, BLACK);
    DrawText(textField->text, textField->textBox.x + 5, textField->textBox.y + 8, 20, BLACK);

    // Dessiner le bouton
    button->pressed = false;
    if (CheckCollisionPointRec(GetMousePosition(), button->rect)) {
        textField->mouseOn = true;
        button->color = BLUE;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            button->pressed = true;
        }
    } else {
        textField->mouseOn = false;
        button->color = RED;
    }

    DrawRectangleRec(button->rect, button->color);
    DrawText(buttonText, button->rect.x + 10, button->rect.y + 8, 20, WHITE);
}
void ajouterValeurManuelle() {
    int valeur;
    printf("Entrez la valeur à ajouter : ");
    scanf("%d", &valeur);
    inserer(&root, valeur);
}


int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Binary Tree Visualizer");

    TextField insertTextField = {{10, 10, 200, 30}, LIGHTGRAY, false, ""};
Button insertButton = {{220, 10, 80, 30}, RED, false};
TextField searchTextField = {{310, 10, 200, 30}, LIGHTGRAY, false, ""};
Button searchButton = {{520, 10, 80, 30}, RED, false};
TextField deleteTextField = {{610, 10, 200, 30}, LIGHTGRAY, false, ""};
Button deleteButton = {{820, 10, 80, 30}, RED, false};

SetTargetFPS(60);

while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    drawButtons(&insertTextField, &insertButton, "Insert");
    drawButtons(&searchTextField, &searchButton, "Search");
    drawButtons(&deleteTextField, &deleteButton, "Delete");
    int key = GetCharPressed();
        if (key != 0) {
            // Ajouter le caractère à la zone de texte appropriée
            if (insertTextField.mouseOn) {
                // Ajouter le caractère à la zone d'insertion
                if (strlen(insertTextField.text) < MAX_INPUT_CHARS) {
                    insertTextField.text[strlen(insertTextField.text)] = (char)key;
                    insertTextField.text[strlen(insertTextField.text) + 1] = '\0';  // Ajouter le caractère de fin de chaîne
                }
            } else if (searchTextField.mouseOn) {
                // Ajouter le caractère à la zone de recherche
                if (strlen(searchTextField.text) < MAX_INPUT_CHARS) {
                    searchTextField.text[strlen(searchTextField.text)] = (char)key;
                    searchTextField.text[strlen(searchTextField.text) + 1] = '\0';
                }
            } else if (deleteTextField.mouseOn) {
                // Ajouter le caractère à la zone de suppression
                if (strlen(deleteTextField.text) < MAX_INPUT_CHARS) {
                    deleteTextField.text[strlen(deleteTextField.text)] = (char)key;
                    deleteTextField.text[strlen(deleteTextField.text) + 1] = '\0';
                }
            }
        }

    // Dessiner l'arbre
    drawNode(root, screenWidth / 2, 80, screenWidth / 4);

    // Mettre à jour le texte des zones de texte
     if (insertButton.pressed) {
            int value = atoi(insertTextField.text);
            inserer(&root, value);
            strcpy(insertTextField.text, "");
        }

        if (searchButton.pressed) {
            int value = atoi(searchTextField.text);
            Node *foundNode = rechercher(root, value);
            if (foundNode != NULL) {
                printf("Node with value %d found!\n", value);
            } else {
                printf("Node with value %d not found.\n", value);
            }
            strcpy(searchTextField.text, "");
        }

        if (deleteButton.pressed) {
            int value = atoi(deleteTextField.text);
            root = supprimer(root, value);
            strcpy(deleteTextField.text, "");
        }

    EndDrawing();
}

CloseWindow();

return 0;
}

