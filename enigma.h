#define ENIGMA_H

#include <iostream>
#include <vector>

#ifndef ROTORS_H
#include "rotors.h"
#endif

#ifndef GLOBAL_H
#include "global.h"
#endif

using namespace std;

class EnigmaMachine {
    public:
        // Constructor //
        EnigmaMachine(char *r_ord, char *r_pos):
            // Choose the three rotors from the settings provided in the constructor parameters //
            r_one((r_ord[0]-48)%5),
            r_two((r_ord[1]-48)%5),
            r_three((r_ord[2]-48)%5),
            r_last(5)
        {
            // Set rotor order //
            r_one.setNext(&r_two);
            r_two.setNext(&r_three);

            // Uppercase the characters in r_pos //
            for(int i = 0; i < 3; i++) if(r_pos[i] > 96) r_pos[i] -= 32;

            for(int i = 0; i < 3; i++) rotPosition[i] = r_pos[i];
            for(int i = 0; i < 3; i++) rotOrder[i] = (r_ord[i]-44)%5+49;

            // Rotate the selected rotors by the values provided in the constructor parameters //
            r_one.forceRotationBy((r_pos[0]+13)%26);
            r_two.forceRotationBy((r_pos[1]+13)%26);
            r_three.forceRotationBy((r_pos[2]+13)%26);
        }

        // Function to decode and encode messages //
        void encode(char *msg) {
            for(int i = 0; i < strlen(msg); i++) {
                if(!((65 <= msg[i] && msg[i] <= 90) || (97 <= msg[i] && msg[i] <= 122))) continue;
                if(transcriptOnConsole) cout << "____ " << msg[i] << " ____\n";
                msg[i] = r_one.transform(msg[i]);
                msg[i] = r_two.transform(msg[i]);
                msg[i] = r_three.transform(msg[i]);
                msg[i] = r_last.transform(msg[i]);
                msg[i] = r_three.antitransform(msg[i]);
                msg[i] = r_two.antitransform(msg[i]);
                msg[i] = r_one.antitransform(msg[i]);
                r_one.rotateBy(1);
                rotPosition[0] = r_one.position + 65;
                rotPosition[1] = r_two.position + 65;
                rotPosition[2] = r_three.position + 65;
                if(transcriptOnConsole) cout << "\n";
            }
        }

        void setRotorsOrder(char *order) {
            r_one.setRotor((order[0]-48)%5);
            r_two.setRotor((order[0]-48)%5);
            r_three.setRotor((order[0]-48)%5);
            for(int i = 0; i < 3; i++) rotOrder[i] = (order[i]-44)%5+49;
            return;
        }

        void setRotorsPositions(char *position) {
            for(int i = 0; i < 3; i++) if(position[i] > 96) position[i] -= 32;

            r_one.setPosition((position[0]+13)%26);
            r_two.setPosition((position[1]+13)%26);
            r_three.setPosition((position[2]+13)%26);
            rotPosition[0] = r_one.position + 65;
            rotPosition[1] = r_two.position + 65;
            rotPosition[2] = r_three.position + 65;
            return;
        }

        char rotOrder[4] = "111";
        char rotPosition[4] = "AAA";

    private:
        // Create three rotors object one for each one of the Virtual Enigma Machine //
        Rotor r_one;
        Rotor r_two;
        Rotor r_three;
        Rotor r_last;
};