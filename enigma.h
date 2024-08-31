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
            // Init plugboard //
            for(int i = 0; i < 26; i++) {
                plugboard[i][0] = i+97;
                plugboard[i][1] = i+97;
            }

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

        // Function to set the rotor to a specific order //
        void setRotorsOrder(char *order) {
            r_one.setRotor((order[0]-48)%5);
            r_two.setRotor((order[0]-48)%5);
            r_three.setRotor((order[0]-48)%5);
            for(int i = 0; i < 3; i++) rotOrder[i] = (order[i]-44)%5+49;
            return;
        }

        // Function to set each rotor to a specific position //
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

        // Function to free a character from the plugboard //
        void unplug(char u) {
            if(u < 97) u += 32;
            if(u < 97 || u > 122) return;

            char n = plugboard[u-97][1];

            plugboard[u-97][1] = plugboard[u-97][0];
            plugboard[n-97][1] = plugboard[n-97][0];

            return;
        }

        // Function to plug two characters in the plugboard //
        void plug(char f, char s) {
            unplug(f); unplug(s);
            
            if(f < 97) f += 32; if(s < 97) s += 32;
            if(f < 97 || f > 122 || s < 97 || s > 122) return;

            plugboard[f-97][1] = s;
            plugboard[s-97][1] = f;

            return;
        }

        // Function to decode and encode messages //
        void encode(char *msg) {
            for(int i = 0; i < strlen(msg); i++) {
                if(!((65 <= msg[i] && msg[i] <= 90) || (97 <= msg[i] && msg[i] <= 122))) continue;

                bool charIsCapital = false;
                if(msg[i] < 96) charIsCapital = true;

                char oldChar = msg[i];
                msg[i] = plugboard[msg[i]-(charIsCapital?65:97)][1] - (charIsCapital?32:0);

                if(transcriptOnConsole) {
                    std::cout << "____ " << oldChar << " ____\n"
                        << "'" << oldChar << "' --> '" << msg[i] << "'\n";
                }
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

                oldChar = msg[i];
                msg[i] = plugboard[msg[i]-(charIsCapital?65:97)][1] - (charIsCapital?32:0);

                if(transcriptOnConsole) {
                    std::cout << "'" << oldChar << "' --> '" << msg[i] << "'\n\n";
                }
            }
        }

        char rotOrder[4] = "111";
        char rotPosition[4] = "AAA";
        char plugboard[26][2];

    private:
        // Create three rotors object one for each one of the Virtual Enigma Machine //
        Rotor r_one;
        Rotor r_two;
        Rotor r_three;
        Rotor r_last;
};