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
void newConsoleLine(EnigmaMachine *VEM);
void runCommand(EnigmaMachine *VEM, char *command);

void notifyDumbError(void);
void encodeMessage(EnigmaMachine *VEM, char *message);
void plugBoard(EnigmaMachine *VEM, char *plugs);
void unplugBoard(EnigmaMachine *VEM, char *plugs, bool unplugAll);
void plugList(EnigmaMachine *VEM);
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
    "   Plugboard: ";
    for(int i = 0; i < 26; i++) if(VEM->plugboard[i][0] < VEM->plugboard[i][1]) std::cout << " " << (char)(VEM->plugboard[i][0]-32) << "/" << (char)(VEM->plugboard[i][1]-32);
    std::cout << "\n\n" <<
    "(type `h` for help, `e` to exit)" <<
    "\n\n";
    return;
}

void newConsoleLine(EnigmaMachine *VEM) {
    cout << "VEM|" << VEM->rotOrder << "-" << VEM->rotPosition << "> ";

    char command[4096];
    cin.getline(command, 4096);

    runCommand(VEM, command);

    return;
}

void runCommand(EnigmaMachine *VEM, char *command) {
    char commandName = '#';
    
    char commandInput[8];
    bool commandGot = false;
    for(int i = 0; i < 8; i++) {
        if(command[i] == ' ') {
            commandGot = true;
            commandInput[i] = '\0';
        }
        else if(!commandGot) commandInput[i] = command[i];
        else commandInput[i] = '\0';
    }
    commandInput[7] = '\0';
    

    if(command[1] == ' ' || command[1] == '\0') commandName = command[0];

    bool unplugAll = (command[2] == '\0') || (command[2] == ' ');

    int startingIndex = -1;
    for(int i = 0; true; i++) {
        if(startingIndex == -1 && command[i] == ' ') startingIndex = i+1;
        else if(startingIndex == -1) continue;
        else command[i-startingIndex] = command[i];
       
        if(command[i] == '\0') break;
    }

    if(startingIndex == -1) command[0] = '\0';

    if(commandName == '-') notifyDumbError();
    else if(commandName == 'm') encodeMessage(VEM, command);
    else if(!strcmp(commandInput, "pB")) plugBoard(VEM, command);
    else if(!strcmp(commandInput, "uB")) unplugBoard(VEM, command, unplugAll);
    else if(!strcmp(commandInput, "pL")) plugList(VEM);
    else if(commandName == 'o') changeRotorsOrder(VEM, command);
    else if(commandName == 'p') changeRotorsPositions(VEM, command);
    else if(commandName == 't') changeTranscriptState(command);
    else if(commandName == 'h') displayHelpPanel();
    else if(commandName == 'e') exit(0);
    
    return;
}

void encodeMessage(EnigmaMachine *VEM, char *message) {
    VEM->encode(message);
    cout << "[SECRET MESSAGE] " << message << "\n";
    return;
}

void plugBoard(EnigmaMachine *VEM, char *plugs) {
    for(int i = 0; plugs[i] && plugs[i+1]; i=i+3) VEM->plug(plugs[i], plugs[i+1]);
    plugList(VEM);
    return;
}

void unplugBoard(EnigmaMachine *VEM, char *plugs, bool unplugAll) {
    if(unplugAll) {
        for(int i = 0; i < 26; i++) VEM->plugboard[i][1] = VEM->plugboard[i][0];
        plugList(VEM);
        return;
    }
    for(int i = 0; strlen(plugs); i++) VEM->unplug(plugs[i]);
    plugList(VEM);
    return;
}

void plugList(EnigmaMachine *VEM) {
    bool plugboardEmpty = true;
    std::cout << "[INFO] Plugboard:";
    for(int i = 0; i < 26; i++)
        if(VEM->plugboard[i][0] < VEM->plugboard[i][1] && ((plugboardEmpty=(plugboardEmpty&&!(VEM->plugboard[i][0] < VEM->plugboard[i][1])))||1))
            std::cout
            << " "
            << (char)(VEM->plugboard[i][0]-32)
            << "/"
            << (char)(VEM->plugboard[i][1]-32);
    
    if(plugboardEmpty) std::cout << " --";
    std::cout << "\n";
    return;
}

void notifyDumbError(void) {
    cout <<
    "[ERROR] It seems you put a '-' before the command, retry without it.\n" <<
    "[SUGGESTION] Read more accurately the help panel, especially the N.B. section.\n";
    return;
}

void changeRotorsOrder(EnigmaMachine *VEM, char *order) {
    char newOrder[4] = "111";
    for(int i = 0; i < 3; i++) newOrder[i] = VEM->rotOrder[i];
    for(int i = 0; i < 3 && order[i] != '\0'; i++) newOrder[i] = order[i];
    newOrder[3] = '\0';
    VEM->setRotorsOrder(newOrder);
    cout << "[INFO] Rotors order changed\n";
}

void changeRotorsPositions(EnigmaMachine *VEM, char *position) {
    char newPosition[4] = "AAA";
    for(int i = 0; i < 3; i++) newPosition[i] = VEM->rotPosition[i];
    for(int i = 0; i < 3 && position[i] != '\0'; i++) newPosition[i] = position[i];
    newPosition[3] = '\0';
    VEM->setRotorsPositions(newPosition);
    cout << "[INFO] Rotors positions changed\n";

}

void changeTranscriptState(char *filename) {
    if(filename[0] == '\0') {
        transcriptOnConsole = !(transcriptOnFile || transcriptOnConsole);
        transcriptOnFile = false;
        if(!transcriptOnConsole) std::cout << "[INFO] Transcripts disabled\n";
        else std::cout << "[INFO] Transcript on console enabled\n";
    }
    else {
        transcriptOnConsole = false;
        transcriptOnFile = true;
        std::cout << "[INFO] Transcript on file enabled\n";
        std::cout << "[ERROR] Unfortunately transicripts on files are not available yet, they'll soon be!\n";
    }
    return;
}

void displayHelpPanel(void) {
    std::cout <<
    "-------------- Virtual Enigma Machine help panel ------------------------------------------\n" <<
    "                                                                                           \n" <<
    "   Commands and arguments in curly braces are {unavailable}                                \n" <<
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
    "  -t       {(filename)}          Enable transcript for each letter path. On the console if \n" <<
    "                                   no filename is specified, otherwise the transcript will \n" <<
    "                                   be saved  in the file with relative path `./<filename>`.\n" <<
    "                                                                                           \n" <<
    "                                                                                           \n" <<
    "Examples:                                                                                  \n" <<
    "   enigma -h                                                                               \n" <<
    "   enigma -o 514 -p glv                                                                    \n" <<
    "   enigma -t myFolder/transcript1.txt                                                      \n" <<
    "   enigma -p FTG tas -t                                                                    \n" <<
    "   enigma -t {conversions.txt} -o 142                                                      \n" <<
    "                                                                                           \n" <<
    "N.B.:                                                                                      \n" <<
    "   Commands in the VEM Console do not change at all. Just keep in mind that must be execut-\n" <<
    "    -ed without the inital `-`.                                                            \n" <<
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