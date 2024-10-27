#include <iostream>
#include <raylib.h>
#include <string>
#include <cstring>

#define MAX_INPUT_CHARS  12
#define MAX_INPUT_NUM 2

using namespace std;

typedef enum GameScreen{input,Hasil}GameScreen;
GameScreen current_Scene = input;

class Data{
    public:
    string Name;
    int Age = 0;
    
    
};

int main (void) {
    Data data;
    bool mouse_on_text = false;
    string Turn="Name";
    const int screenWidth = 800;
    const int screenHeight = 600;
    int letterCount = 0;
    char name[MAX_INPUT_CHARS+1] = "\0";
    int ageInputCount = 0;
    Rectangle textBox = { screenWidth/2.0f - 100, 180, 225, 50 };
    

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        //DrawTexture(tictactoeBG,200,200,WHITE);
        if (CheckCollisionPointRec(GetMousePosition(),textBox)){
            mouse_on_text = true;
        }
        else mouse_on_text = false;

        if (mouse_on_text == true){
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetCharPressed();
            if (Turn == "Name") {
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                        name[letterCount] = (char)key;
                        name[letterCount + 1] = '\0';
                        letterCount++;
                    }
                    key = GetCharPressed();
                }
                data.Name = name;
            } else if (Turn == "Age") {
                while (key > 0) {
                    if (key >= '0' && key <= '9' && ageInputCount < 3) {
                        data.Age = data.Age * 10 + (key - '0');
                        ageInputCount++;
                    }
                    key = GetCharPressed();
                }
            }
            

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                 if (Turn == "Name" && letterCount > 0) {
                    letterCount--;
                    name[letterCount] = '\0';
                } else if (Turn == "Age" && ageInputCount > 0) {
                    data.Age /= 10;
                    ageInputCount--;
                }
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        BeginDrawing();
        ClearBackground(BLUE);
        switch (current_Scene)
        {
            case input:{
                DrawRectangleRec(textBox,LIGHTGRAY);
                if (mouse_on_text) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
                else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

                if (Turn=="Name"){
                    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
                    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
                    DrawText("Masukan Nama: ", 315, 100, 40, DARKGRAY);
                    
                    
                }
                else if(Turn=="Age"){
                    DrawText(TextFormat("%i", data.Age), (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
                    DrawText("Masukan Umur: ", 315, 100, 40, DARKGRAY);
                    

                }
            }break;
            case Hasil:{
                
                DrawText(TextFormat("Umur : %i", data.Age), 315, 250, 40, DARKGRAY);
                DrawText(TextFormat("Nama : %s", data.Name.c_str()), 315, 100, 40, DARKGRAY);
                //DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
                //DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
            }
        }


        
        if (IsKeyPressed(KEY_ENTER)){
            if (Turn=="Name")Turn="Age";
            else if (Turn=="Age")current_Scene=Hasil;
        }


        EndDrawing();  
    }
    

    CloseWindow();
    return 0;
}