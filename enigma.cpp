#include <iostream>
#include <string>

#ifndef ENIGMA_H
#include "enigma.h"
#endif

#ifndef  UTILIS_H
#include "utilis.h"
#endif

#ifndef GLOBAL_H
#include "global.h"
#endif

using namespace std;

// Define constants for the number of rotors used and for the maximum lenght of the message //
#define ROT_USED 3
#define MAX_LEN 32768

int main(int argc, char *argv[]) {
    int orderIndex = 0, positionIndex = 0, transcriptIndex = 0, helpIndex = 0;

    for(int i = 0; i < argc; i++) {
        if (orderIndex == 0 && !strcmp(argv[i], "-o")) {
            orderIndex = i;
            continue;
        }
        else if (positionIndex == 0 && !strcmp(argv[i], "-p")) {
            positionIndex = i;
            continue;
        }
        else if (transcriptIndex == 0 && !strcmp(argv[i], "-t")) {
            transcriptIndex = i;
            continue;
        }
        else if(helpIndex == 0 && !strcmp(argv[i], "-h")) {
            helpIndex = i;
            cout << "\n";
            displayHelpPanel();
            return 0;
        }
    }

    if(transcriptIndex) {
        if(!argv[transcriptIndex+1] || argv[transcriptIndex+1][0] == '-') transcriptOnConsole = true;
        else transcriptOnFile = true;
    }

    // Get the VEM setup //
    if(orderIndex) str_cpy(rotorsOrder, argv[orderIndex+1]);
    if(positionIndex) str_cpy(rotorsPosition, argv[positionIndex+1]);

    EnigmaMachine VEM(rotorsOrder, rotorsPosition);

    printInitialDashboard(&VEM);

    while(1) newConsoleLine(&VEM);

    return 0;
}

void transformText(EnigmaMachine *Enigma) {
    // Create a variable where to store the string to transform //
    char message[MAX_LEN];

    // Get text to transform //
    cout << "\nInsert the text here:\n";
    cin.ignore();
    cin.getline(message, MAX_LEN);

    // Transform text //
    Enigma->encode(message);

    // Output the transoformed text
    cout << "Transformed text:\n" << message;

}