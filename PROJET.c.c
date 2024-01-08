#include<raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Node {
    int data ; 
   struct  Node*left ;
   struct Node*right ;
};
 struct Node *create(int value){
   struct Node*Newnode = malloc(sizeof(struct Node));
     Newnode->data = value ;
     Newnode->left = NULL;
     Newnode->right = NULL;
     return Newnode;
 }
 
   void DrawNode(const char*msg) {
    const int X = 900 / 2;
    const int Y = 600 / 2;
    DrawCircle(X, Y, 40, BLACK);
    DrawText(msg, X - 20, Y - 20, 50, GREEN);


}

 int main(){
     //*************************here raylib*******************
    const int WIDTH  = 900;
    const int  HEIGHT = 600; 
    InitWindow(WIDTH, HEIGHT, "TREEVISUALTION");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const char msg1[40] = "WELCOME TO VISUAL ALGORTIHM ";
        const char msg2[40] = "Here is the binary tree";
        DrawTextEx(GetFontDefault(), msg1, (Vector2){ 180, 20 }, 40, 3, BLACK);
        DrawTextEx(GetFontDefault(), msg2, (Vector2){ 200, 70 }, 20, 2, GREEN);
      char* msg3 = strdup("2");
       char* msg4 = strdup("1");
      struct Node *root = create(2);

      DrawNode(msg3);
        EndDrawing();
    }
    CloseWindow();
    //**************here end of raylib**********
     // root->left = create(1);
      //root->right = create(3);
      //root->left->left = create(5);
      //root->left->right = create(6);
      //root->right->right = create(8);
      //root->right->left = create(9);
      return 0 ;
 }
 
