#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

map<char, string> charToMorse;
map<string, char> morseToChar;

void initializeMorse() {
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' '};
                     
    string morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
                      ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                      "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
                      ".----", "..---", "...--", "....-", ".....", "-....", "--...",
                      "---..", "----.", "-----", "/"};

    int size = sizeof(letters) / sizeof(letters[0]);
    for (int i = 0; i < size; i++) {
        charToMorse[letters[i]] = morse[i];
        morseToChar[morse[i]] = letters[i];
    }
}

string textToMorse(string text) {
    string result = "";
    for (char c : text) {
        c = toupper(c);
        if (charToMorse.find(c) != charToMorse.end()) {
            result += charToMorse[c] + " ";
        }
    }
    return result;
}

string morseToText(string morse) {
    string result = "";
    stringstream ss(morse);
    string word;

    while (ss >> word) {
        if (morseToChar.find(word) != morseToChar.end()) {
            result += morseToChar[word];
        }
    }
    return result;
}

int main() {
    initializeMorse();
    int choice;

    cout << "=== Morse Code Translator ===\n";
    cout << "1. Text to Morse\n";
    cout << "2. Morse to Text\n";
    cout << "Choose an option (1 or 2): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string text;
        cout << "Enter the text: ";
        getline(cin, text);
        cout << "Morse: " << textToMorse(text) << endl;
    } 
    else if (choice == 2) {
        string morse;
        cout << "Enter the Morse code (separate letters with spaces and words with /): ";
        getline(cin, morse);
        cout << "Text: " << morseToText(morse) << endl;
    } 
    else {
        cout << "Invalid option!" << endl;
    }

    return 0;
}