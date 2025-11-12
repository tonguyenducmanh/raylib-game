#include "raylib.h"
#include <string.h>

// Function to draw text with black background and white border
void DrawTextBoxed(const char *text, int posX, int posY, int fontSize, Color bgColor, Color textColor, Color borderColor, int borderSize) {
    int textWidth = MeasureText(text, fontSize);
    int padding = 4;
    
    // Draw border
    DrawRectangle(posX - padding - borderSize, posY - padding - borderSize, 
                  textWidth + padding * 2 + borderSize * 2, 
                  fontSize + padding * 2 + borderSize * 2, borderColor);
    
    // Draw background
    DrawRectangle(posX - padding, posY - padding, 
                  textWidth + padding * 2, 
                  fontSize + padding * 2, bgColor);
    
    // Draw text
    DrawText(text, posX, posY, fontSize, textColor);
}

// Function to draw text with border only (no background)
void DrawTextBordered(const char *text, int posX, int posY, int fontSize, Color textColor, Color borderColor, int borderSize) {
    int textWidth = MeasureText(text, fontSize);
    int padding = 4;
    
    // Draw border only
    DrawRectangleLines(posX - padding - borderSize, posY - padding - borderSize, 
                       textWidth + padding * 2 + borderSize * 2, 
                       fontSize + padding * 2 + borderSize * 2, borderColor);
    
    // Draw text
    DrawText(text, posX, posY, fontSize, textColor);
}

// Function to calculate total width of text line with spacing
int CalculateLineWidth(const char *parts[], int count, int fontSize, int spacing) {
    int totalWidth = 0;
    for (int i = 0; i < count; i++) {
        totalWidth += MeasureText(parts[i], fontSize);
        if (i < count - 1) totalWidth += spacing;
    }
    return totalWidth;
}

int main(void) {
    const int screenWidth = 500;
    const int screenHeight = 300;

    InitWindow(screenWidth, screenHeight, "ToManh's tools");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw main black square (centered)
        int squareSize = 140;
        int squareX = (screenWidth - squareSize) / 2;
        int squareY = 40;
        DrawRectangle(squareX, squareY, squareSize, squareSize, BLACK);
        DrawRectangle(squareX + 8, squareY + 8, squareSize - 16, squareSize - 16, WHITE);

        // Draw "tomanh" text inside square (centered)
        const char *raylibText = "tomanh";
        int raylibWidth = MeasureText(raylibText, 20);
        DrawText(raylibText, squareX + (squareSize - raylibWidth) - 20, squareY + 108, 20, BLACK);

        // Draw bottom text line 1:
        const char *line1_parts[] = {"The", "easy", "way", "to-learn", "something"};
        int line1Y = 200;
        int spacing = 10; // Khoảng cách giữa các từ
        int line1Width = CalculateLineWidth(line1_parts, 5, 20, spacing);
        int currentX = (screenWidth - line1Width) / 2;
        
        for (int i = 0; i < 5; i++) {
            if (line1_parts[i] == "easy" || line1_parts[i] == "to-learn") {
                DrawTextBoxed(line1_parts[i], currentX, line1Y, 20, BLACK, WHITE, BLACK, 2);
            } else {
                DrawText(line1_parts[i], currentX, line1Y, 20, BLACK);
            }
            currentX += MeasureText(line1_parts[i], 20) + spacing;
        }

        // Draw bottom text line 2
        const char *line2_parts[] = {"is just", "do", "it", "the hard way"};
        int line2Y = 240;
        int line2Width = CalculateLineWidth(line2_parts, 4, 20, spacing);
        currentX = (screenWidth - line2Width) / 2;
        
        for (int i = 0; i < 4; i++) {
            if (line2_parts[i] == "do") {
                DrawTextBoxed(line2_parts[i], currentX, line2Y, 20, BLACK, WHITE, BLACK, 2);
            } else if (line2_parts[i] == "the hard way") {
                DrawTextBordered(line2_parts[i], currentX, line2Y, 20, BLACK, BLACK, 2);
            } else {
                DrawText(line2_parts[i], currentX, line2Y, 20, BLACK);
            }
            currentX += MeasureText(line2_parts[i], 20) + spacing;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}