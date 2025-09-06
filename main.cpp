#include "raylib.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct Button {
    Rectangle rect;
    string text;
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Nyx IDE");
    SetTargetFPS(60);

    vector<string> lines;
    string currentLine;
    int scrollOffset = 0;

    // Buttons
    Button runBtn   = {{650, 50, 100, 40}, "Run"};
    Button saveBtn  = {{650, 100, 100, 40}, "Save"};
    Button loadBtn  = {{650, 150, 100, 40}, "Load"};
    Button exitBtn  = {{650, 200, 100, 40}, "Exit"};

    while (!WindowShouldClose()) {
        // Input: simple line editing (type characters, press Enter to add)
        int key = GetCharPressed();
        if (key > 0 && key < 128) currentLine += (char)key;

        if (IsKeyPressed(KEY_BACKSPACE) && !currentLine.empty())
            currentLine.pop_back();

        if (IsKeyPressed(KEY_ENTER)) {
            lines.push_back(currentLine);
            currentLine.clear();
            if ((int)lines.size() > 20) scrollOffset++;
        }

        // Mouse input for buttons
        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePos, runBtn.rect)) {
                // Run code (placeholder)
                stringstream ss;
                for (auto& l : lines) {
                    if (l.find("io::out") != string::npos) {
                        size_t start = l.find("(");
                        size_t end = l.find(")");
                        if (start != string::npos && end != string::npos && end > start)
                            ss << l.substr(start+1, end-start-1) << "\n";
                    }
                }
                lines.push_back("[Run Output]");
                string line;
                while (getline(ss, line))
                    lines.push_back(line);
            }
            else if (CheckCollisionPointRec(mousePos, saveBtn.rect)) {
                ofstream out("program.nyx");
                for (auto& l : lines) out << l << "\n";
                out.close();
            }
            else if (CheckCollisionPointRec(mousePos, loadBtn.rect)) {
                ifstream in("program.nyx");
                if (in.is_open()) {
                    lines.clear();
                    string l;
                    while (getline(in, l)) lines.push_back(l);
                    in.close();
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn.rect)) {
                break;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(20, 20, 600, 560, LIGHTGRAY);

        int y = 30;
        for (size_t i = scrollOffset; i < lines.size(); i++) {
            DrawText(lines[i].c_str(), 30, y, 20, BLACK);
            y += 25;
            if (y > 550) break;
        }

        // Draw current typing line
        DrawText(currentLine.c_str(), 30, y, 20, BLUE);

        // Draw buttons
        DrawRectangleRec(runBtn.rect, GRAY); DrawText(runBtn.text.c_str(), runBtn.rect.x+10, runBtn.rect.y+10, 20, WHITE);
        DrawRectangleRec(saveBtn.rect, GRAY); DrawText(saveBtn.text.c_str(), saveBtn.rect.x+10, saveBtn.rect.y+10, 20, WHITE);
        DrawRectangleRec(loadBtn.rect, GRAY); DrawText(loadBtn.text.c_str(), loadBtn.rect.x+10, loadBtn.rect.y+10, 20, WHITE);
        DrawRectangleRec(exitBtn.rect, GRAY); DrawText(exitBtn.text.c_str(), exitBtn.rect.x+10, exitBtn.rect.y+10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}