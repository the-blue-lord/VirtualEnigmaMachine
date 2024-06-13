#include <iostream>
#include "utilis.h"

using namespace std;

// Define constants for the number of rotors used and for the maximum lenght of the message //
#define ROT_USED 3
#define MAX_LEN 256

int main() {
    // Create two variables to store the machine setup //
    char rotorsOrder[] = "123";
    char rotorsPosition[] = "00-00-00";

    // Create two variables where to store the input text and the encripted/decripted text //
    char oldText[MAX_LEN];
    char mewText[MAX_LEN];

    // Get the machine setup //
    cout << "\n";
    get_rotorsOrder(rotorsOrder);
    get_rotorsPosition(rotorsPosition);

    // Get text to transform //
    cout << "\nInsert the text here:\n";
    cin >> oldText;

    // Transform text //
    

    // Output the trasnofrmed text

    return 0;
}