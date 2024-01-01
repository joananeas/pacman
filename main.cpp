#include <iostream>
#include <conio.h>

int main() {
    char key;
    
    while (true) {
        key = _getch();
        
        if (key == 'q') {
            break;
        }
        
        std::cout << "Key pressed: " << key << std::endl;
    }
    
    return 0;
}
