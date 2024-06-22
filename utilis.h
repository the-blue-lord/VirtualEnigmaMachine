#define UTILIS_H

#include <iostream>
#include <cstring>

using namespace std;

void str_cpy(char *des, const char *ori);

void get_rotorsOrder(char *order_storer);
void get_rotorsPosition(char *position_storer);

int sendHelpMessage();

void get_rotorsOrder(char *order_storer) {
    char user_order[4];

    cout << "Choose the rotors order: ";
    cin >> user_order;
    
    user_order[3] = '\0';

    str_cpy(order_storer, user_order);
    
    return;
}

void get_rotorsPosition(char *position_storer) {
    char user_position[4];

    cout << "Choose the inital rototors position: ";
    cin >> user_position;
    
    user_position[3] = '\0';

    str_cpy(position_storer, user_position);

    return;
}

void str_cpy(char *des, const char *ori) {
    for(int i = 0; i < strlen(ori); i++) {
        if(des[i] == '\0') break;
        des[i] = ori[i];
    }

    return;
}

int sendHelpMessage() {
    cout <<
    "                                                                                           \n" <<
    "                                                                                           \n" <<
    "                                                                                           \n" <<
    "-------------- Virtual Enigma Machine help panel ------------------------------------------\n" <<
    "                                                                                           \n" <<
    "   Commands and arguments in square brackets are [necessary]                               \n" <<
    "   Commands and arguments in round brackets are (optional)                                 \n" <<
    "                                                                                           \n" <<
    "Command:   Arguments:          Description:                                                \n" <<
    "                                                                                           \n" <<
    "  (-h)       - none -            Display this help message.                                \n" <<
    "                                                                                           \n" <<
    "  (-o)       [number]            Specify the rotors order, you can choose three rotors from\n" <<
    "                                   a list of 5 presetted rotors. Therefore the <number> mu-\n" <<
    "                                   -st be a three digit number (one digit for each rotor)  \n" <<
    "                                   composed of digits 1 through 5 (each representing one r-\n" <<
    "                                   -otor). To any digit greater than 5, will be subtracted \n" <<
    "                                   5 (0 will be evaluated as 5). Any other digit will be t-\n" <<
    "                                   -runcated. Any missing digit will be replaced with a 1. \n" <<
    "                                   Any character different from a digit will be replaced r-\n" <<
    "                                   -andomly.                                               \n" <<
    "                                                                                           \n" <<
    "  (-p)       [string]            Specify the starting rotors positions, each position is r-\n" <<
    "                                   -epresented by a letter. Thus the <string> must be comp-\n" <<
    "                                   -osed of exactly three letters. Any other character will\n" <<
    "                                   be truncated. Any missing character will be replaced wi-\n" <<
    "                                   -th an 'A'. Any character different from a letter will  \n" <<
    "                                   be replaced with a random letter.                       \n" <<
    "                                                                                           \n" <<
    "  (-t)       (filename)          Enable transcript for each letter path. On the console if \n" <<
    "                                   no filename is specified, the transcript will be saved  \n" <<
    "                                   in the file with relative path ```./<filename>```.      \n" <<
    "                                                                                           \n" <<
    "                                                                                           \n";

    return 0;
}