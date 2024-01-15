#include <raylib.h>
#include <stdlib.h>

#define MAX_INPUT_CHARS 20
#define RADIUS 25

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct button {
    Rectangle rect;
    Color color;
    bool pressed;
} Button;

typedef struct TextField {
    Rectangle textBox;
    Color color;
    bool mouseOn;
    bool cursorActive; 
    char text[MAX_INPUT_CHARS + 1];
    int textSize;
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

    int key = GetKeyPressed();  // Utilisez GetKeyPressed() au lieu de GetCharPressed()

    // Vérifiez si la touche est alphanumérique
    if ((key >= '0' && key <= '9') && strlen(textField->text) < MAX_INPUT_CHARS) {
        // Ajouter le caractère pressé à textField->text
        int length = strlen(textField->text);
        textField->text[length] = (char)key;
        textField->text[length + 1] = '\0';  // Null-terminate the string
        textField->textSize++; // Increment text size
    }

    // Dessiner le bouton
    button->pressed = false;
    if (CheckCollisionPointRec(GetMousePosition(), button->rect)) {
        textField->mouseOn = true;
        button->color = BLUE;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            button->pressed = true;
            textField->cursorActive = true; // Activer le curseur lors du clic
        }
    } else {
        textField->mouseOn = false;
        button->color = RED;
    }
    if (IsKeyPressed(KEY_BACKSPACE) && textField->textSize > 0) {
        textField->textSize--;
        textField->text[textField->textSize] = '\0'; // Null-terminate the string
    }

    DrawRectangleRec(button->rect, button->color);
    DrawText(buttonText, button->rect.x + 10, button->rect.y + 8, 20, WHITE);

    if (textField->cursorActive && ((GetTime() - (int)GetTime()) < 0.5f)) {
        int cursorX = MeasureText(textField->text, textField->textSize) + textField->textBox.x + 5;
        DrawLine(cursorX, textField->textBox.y + 2, cursorX, textField->textBox.y + textField->textBox.height - 4, BLACK);
    }

    DrawText(textField->text, textField->textBox.x + 5, textField->textBox.y + 8, 20, BLACK);
}


void HandleTextFieldInput(TextField *textField, Button *button, int enterKey) {
    int key = GetKeyPressed();
    
    if (key != 0 && key != enterKey && key != KEY_BACKSPACE && strlen(textField->text) < MAX_INPUT_CHARS) {
        // Ajouter le caractère pressé à textField->text
        int length = strlen(textField->text);
        textField->text[length] = (char)key;
        textField->text[length + 1] = '\0';
        textField->textSize++;
    }

    // Gestion de la touche Entrée
    if (IsKeyPressed(KEY_ENTER) && textField->textSize > 0) {
        // Traiter la valeur saisie, par exemple, rechercher ou supprimer
        int value = atoi(textField->text);
        // Ajoutez ici le code pour rechercher ou supprimer selon vos besoins
        // Réinitialiser la zone de texte
        strcpy(textField->text, "");
        textField->textSize = 0;
    }

    // Gestion de la touche Retour arrière (Backspace)
    if (key == KEY_BACKSPACE && textField->textSize > 0) {
        textField->textSize--;
        textField->text[textField->textSize] = '\0'; // Terminer la chaîne
    }
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
//Initialisation de l'echelle de l'hauteur d'arbre
 float   levelHeight= 50.0f;
SetTargetFPS(60);
  Font customFont = LoadFontEx("Poppins-Black.ttf", 50, 0,0);
    Font font =  LoadFontEx("Poppins-Medium.ttf", 20, 0, 0);
    Font fontbot =  LoadFontEx("Poppins-Medium.ttf", 18, 0, 0);


while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Afficher du texte supplémentaire
    DrawText("Entrez une valeur et appuyez sur 'Insérer' pour l'ajouter à l'arbre.", 10, 70, 20, BLACK);

    drawButtons(&insertTextField, &insertButton, "Insérer");
    drawButtons(&searchTextField, &searchButton, "Rechercher");
    drawButtons(&deleteTextField, &deleteButton, "Supprimer");

    // Saisie de texte pour l'insertion
    HandleTextFieldInput(&insertTextField, &insertButton, KEY_ENTER);

    // Saisie de texte pour la recherche
    HandleTextFieldInput(&searchTextField, &searchButton, KEY_ENTER);

    // Saisie de texte pour la suppression
    HandleTextFieldInput(&deleteTextField, &deleteButton, KEY_ENTER);

    drawNode(root, screenWidth / 2, 80, screenWidth / 4);

    if (insertButton.pressed) {
        int value = atoi(insertTextField.text);
        inserer(&root, value);
    }

    if (searchButton.pressed) {
        int value = atoi(searchTextField.text);
        Node *foundNode = rechercher(root, value);
        if (foundNode != NULL) {
            printf("Nœud avec la valeur %d trouvé !\n", value);
        } else {
            printf("Nœud avec la valeur %d non trouvé.\n", value);
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
}