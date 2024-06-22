#include <iostream>
#include <cstring>

using namespace std;

void str_cpy(char *des, const char *ori);
void get_rotorsOrder(char *order_storer);
void get_rotorsPosition(char *position_storer);

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