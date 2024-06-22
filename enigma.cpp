#include <iostream>
#include <string>
#include "enigma.h"

using namespace std;

// Define constants for the number of rotors used and for the maximum lenght of the message //
#define ROT_USED 3
#define MAX_LEN 32768

int main(int argc, char *argv[]) {
    // Create two variables to store the machine setup //
    char rotorsOrder[] = "123";
    char rotorsPosition[] = "AAA";

    // Create a variable where to store the string to transform //
    char message[MAX_LEN];

    // Get the machine setup //
    cout << "\n";
    get_rotorsOrder(rotorsOrder);
    get_rotorsPosition(rotorsPosition);

    // Get text to transform //
    cout << "\nInsert the text here:\n";
    cin.ignore();
    cin.getline(message, MAX_LEN);

    // Transform text //
    EnigmaMachine Enigma(rotorsOrder, rotorsPosition);
    Enigma.encode(message);

    // Output the transoformed text
    cout << "Transformed text:\n" << message;

    return 0;
}