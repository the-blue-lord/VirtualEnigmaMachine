#define UTILIS_H

#include <iostream>
#include <cstring>

#ifndef ENIGMA_H
#include "enigma.h"
#endif

#ifndef GLOBAL_H
#include "global.h"
#endif

using namespace std;

void str_cpy(char *des, const char *ori);

void displayHelpPanel(void);

void printInitialDashboard(EnigmaMachine *VEM);
void newTerminalLine(EnigmaMachine *VEM);
void runCommand(EnigmaMachine *VEM, char *command);

void notifyDumbError(void);
void encodeMessage(EnigmaMachine *VEM, char *message);
void changeRotorsOrder(EnigmaMachine *VEM, char *order);
void changeRotorsPositions(EnigmaMachine *VEM, char *position);
void changeTranscriptState(char *filename);

void flush_istream(void);

void str_cpy(char *des, const char *ori) {
    for(int i = 0; i < strlen(ori); i++) {
        if(des[i] == '\0') break;
        des[i] = ori[i];
    }

    return;
}

void printInitialDashboard(EnigmaMachine *VEM) {
    cout <<
    "VEM Settings:\n" <<
    "   Rotors:     " <<  VEM->rotOrder[0]   << " - " <<  VEM->rotOrder[1]   << " - " <<  VEM->rotOrder[2]   << "\n" <<
    "   Position:   " << VEM->rotPosition[0] << " - " << VEM->rotPosition[1] << " - " << VEM->rotPosition[2] << "\n" <<
    "\n" <<
    "(type `h` for help, `e` to exit)" <<
    "\n\n";
    return;
}

void newTerminalLine(EnigmaMachine *VEM) {
    cout << "VEM|" << VEM->rotOrder << "-" << VEM->rotPosition << "> ";

    char command[4096];
    cin.getline(command, 4096);

    runCommand(VEM, command);

    return;
}

void runCommand(EnigmaMachine *VEM, char *command) {
    char commandName = command[0];

    bool thereAreArguments = (command[1] == ' ');

    char commandArgument[4096];
    for(int i = 0; i < 4096; i++) commandArgument[i] = '\0';
    if(thereAreArguments) for(int i = 0; i < 4094 && command[i+2] != '\0'; i++) commandArgument[i] = command[i+2];

    if(commandName == '-') notifyDumbError();
    else if(commandName == 'm') encodeMessage(VEM, commandArgument);
    else if(commandName == 'o') changeRotorsOrder(VEM, commandArgument);
    else if(commandName == 'p') changeRotorsPositions(VEM, commandArgument);
    else if(commandName == 't') changeTranscriptState(commandArgument);
    else if(commandName == 'h') displayHelpPanel();
    else if(commandName == 'e') exit(0);
    
    return;
}

void encodeMessage(EnigmaMachine *VEM, char *message) {
    VEM->encode(message);
    cout << "[SECRET MESSAGE] " << message << "\n";
    return;
}

void notifyDumbError(void) {
    cout <<
    "[ERROR] It seems you put a '-' before the command, retry without it.\n" <<
    "[SUGGESTION] Read more accurately the help panel, especially the N.B. section.\n";
    return;
}

void changeRotorsOrder(EnigmaMachine *VEM, char *order) {
    cout << "[INFO] Changing rotors order...\n";
    char newOrder[4] = "111";
    for(int i = 0; i < 3; i++) newOrder[i] = VEM->rotOrder[i];
    for(int i = 0; i < 3 && order[i] != '\0'; i++) newOrder[i] = order[i];
    newOrder[3] = '\0';
    VEM->setRotorsOrder(newOrder);
}

void changeRotorsPositions(EnigmaMachine *VEM, char *position) {
    cout << "[INFO] Changing rotors positions...\n";
    char newPosition[4] = "AAA";
    for(int i = 0; i < 3; i++) newPosition[i] = VEM->rotPosition[i];
    for(int i = 0; i < 3 && position[i] != '\0'; i++) newPosition[i] = position[i];
    newPosition[3] = '\0';
    VEM->setRotorsPositions(newPosition);

}

void changeTranscriptState(char *filename) {
    cout << "[ERROR] Unfortunately transicripts are not available yet, they'll soon be\n";
    return;
}

void displayHelpPanel(void) {
    cout <<
    "-------------- Virtual Enigma Machine help panel ------------------------------------------\n" <<
    "                                                                                           \n" <<
    "   Commands in curly braces are {unavailable}                                              \n" <<
    "   Arguments in square brackets are [necessary]                                            \n" <<
    "   Arguments in round brackets are (optional)                                              \n" <<
    "                                                                                           \n" <<
    "Command:   Arguments:          Description:                                                \n" <<
    "                                                                                           \n" <<
    "  -o         [number]            Specify the rotors order, you can choose three rotors from\n" <<
    "                                   a list of 5 presetted rotors. Therefore the <number> mu-\n" <<
    "                                   -st be a three digit number (one digit for each rotor)  \n" <<
    "                                   composed of digits 1 through 5 (each representing one r-\n" <<
    "                                   -otor). To any digit greater than 5, will be subtracted \n" <<
    "                                   5 (0 will be evaluated as 5). Any other digit will be t-\n" <<
    "                                   -runcated. Any missing digit will be replaced with a 1. \n" <<
    "                                   Any character different from a digit will be replaced r-\n" <<
    "                                   -andomly.                                               \n" <<
    "                                                                                           \n" <<
    "  -p         [string]            Specify the starting rotors positions, each position is r-\n" <<
    "                                   -epresented by a letter. Thus the <string> must be comp-\n" <<
    "                                   -osed of exactly three letters. Any other character will\n" <<
    "                                   be truncated. Any missing character will be replaced wi-\n" <<
    "                                   -th an 'A'. Any character different from a letter will  \n" <<
    "                                   be replaced with a random letter.                       \n" <<
    "                                                                                           \n" <<
    "  -h         - none -            Display this help message.                                \n" <<
    "                                                                                           \n" <<
    "  -t         (filename)          Enable transcript for each letter path. On the console if \n" <<
    "                                   no filename is specified, otherwise the transcript will \n" <<
    "                                   be saved  in the file with relative path `./<filename>`.\n" <<
    "                                                                                           \n" <<
    "                                                                                           \n" <<
    "Examples:                                                                                  \n" <<
    "   enigma -h                                                                               \n" <<
    "   enigma -o 514 -p glv                                                                    \n" <<
    "   enigma -t myFolder/transcript1.txt                                                      \n" <<
    "   enigma -p FTG tas -t                                                                        \n" <<
    "   enigma -t conversions.txt -o 142                                                        \n" <<
    "                                                                                           \n" <<
    "N.B.:                                                                                      \n" <<
    "   Commands in the VEM terminal do not change at all. Just keep in mind that must be execu-\n" <<
    "    -ted without the inital `-`.                                                           \n" <<
    "                                                                                           \n" <<
    "-------------------------------------------------------------------------------------------\n" <<
    "                                                                                           \n";

    return;
}

void flush_istream(void) {
    std::string temp;
    getline(std::cin, temp);
    return;
}