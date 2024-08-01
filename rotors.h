#define ROTORS_H

#include <iostream>
#include <string.h>

#ifndef GLOBAL_H
#include "global.h"
#endif

using namespace std;

class Rotor {
    public:
        // Class constructor //
        Rotor(int r_num) {
            setRotor(r_num);
        }

        void setRotor(int r_num) {
            
            // Get the five possible rotors plus the reflector//
            const char *transform_factor_builder[6] = {
                "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // Rotor I
                "AJDKSIRUXBLHWTMCQGZNPYFVOE", // Rotor II
                "BDFHJLCPRTXVZNYEIWGAKMUSQO", // Rotor III
                "ESOVPZJAYQUIRHXLNFTGKDCMWB", // Rotor IV
                "VZBRGITYUPSDNHLXAWMJQOFECK", // Rotor V
                "EJMZALYXVBWFCRQUONTSPIKHGD"  // Reflector
            };

            // Copy the choosen rotor as the transform factor //
            strcpy(transform_factor, transform_factor_builder[r_num]);

            return;
        }

        // Function to transform letters as Enigma Machine rotors //
        char transform(char c) {
            if(transcriptOnConsole) cout << "'" << c << "' --> ";
            // Check if the character is a letter //
            bool charIsLetter = (65 <= c && c <= 90) || (97 <= c && c <= 122);
            // If it isn't return the character unchanged //
            if(!charIsLetter) return c;

            // Memorize if the character is lowercase //
            bool charIsLowercase = (c > 96);

            // If it's lowercase uppercase it //
            if(charIsLowercase) c -= 32;

            // Convert the range 65-90(A-Z) to 0-25 //
            c -= 65;
            // Shift the number by the position of the rotor //
            c += position;
            while(c < 0) c += 26; c %= 26;

            // Transform the character given //
            c = transform_factor[c];
            
            // Convert the range 65-90(A-Z) to 0-25 //
            c -= 65;
            // Shift the number backwards by the position of the rotor //
            c -= position;
            while(c < 0) c += 26; c %= 26;
            // Convert the range 0-25 to 65-90(A-Z) //
            c += 65;

            // If it was lowercase, lowercase it //
            if(charIsLowercase) c += 32;

            if(transcriptOnConsole) cout << "'" << c << "'\n";

            // Return the character //
            return c;
        }
        
        // Function to transform backwards letters as Enigma Machine rotors //
        char antitransform(char c) {
            if(transcriptOnConsole) cout << "'" << c << "' --> ";
            // Check if the character is a letter //
            bool charIsLetter = (65 <= c && c <= 90) || (97 <= c && c <= 122);
            // If it isn't return the character unchanged //
            if(!charIsLetter) return c;

            // Memorize if the character is lowercase //
            bool charIsLowercase = (c > 96);

            // If it's lowercase uppercase it //
            if(charIsLowercase) c -= 32;

            // Convert the range 65-90(A-Z) to 0-25 //
            c -= 65;
            // Shift the number by the position of the rotor //
            c += position;
            while(c < 0) c += 26; c %= 26;

            // Find the index of the character in the rotor array //
            int index = 0;
            for(index = 0; index < 26; index++) if(transform_factor[index] == c+65) break;

            // Not transforming the index to a letter by adding 65 to preserve the range 0-25 //
            c = index;

            // Shift the number backwards by the position of the rotor //
            c -= position;
            while(c < 0) c += 26; c %= 26;
            // Convert the range 0-25 to 65-90(A-Z) //
            c += 65;

            // If it was lowercase, lowercase it //
            if(charIsLowercase) c += 32;

            if(transcriptOnConsole) cout << "'" << c << "'\n";

            // Return the character //
            return c;
        }

        // Function to rotate the rotor by a specific value //
        void rotateBy(int i) {
            // Increase the position of the rotor by the specified value //
            position += i;
            // Rotate the next rotor by the number of complete turns the rotor has done //
            rotateNextBy((int)(position/26));
            // Reset the position in a range 0-25 //
            while(position < 0) position += 26; position %= 26;

            return;
        }

        // Function to rotate the rotor by a specific value without affecting the other rotor positions //
        void forceRotationBy(int i) {
            // Increase the position of the rotor by the specified value //
            position += i;
            // Reset the position in a range 0-25 //
            position %= 26;

            return;
        }

        // Function to set the next rotor in the sequence //
        void setNext(Rotor *next_rotor) {
            r_next = next_rotor;
            return;
        }

        void setPosition(int newPos) {
            position = newPos;
            return;
        }
        
        // Create an integer to store the position of the rotor //
        int position = 0;

    private:
        // Create an array of characters to manage the transformation of letters //
        char transform_factor[27];
        // Create a pointer to point to the next rotor //
        Rotor *r_next = nullptr;

        // Function to rotate the next rotor by a given value //
        void rotateNextBy(int i) {
            // If there's no next rotor or the rotation value is 0 return //
            if(!r_next || i == 0) return;
            // Else rotate the next rotor //
            r_next->rotateBy(i);

            return;
        }
};