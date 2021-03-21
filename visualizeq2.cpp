#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    // cout << "\r" << 2 << "% completed.       " << flush;
    // sleep (2);
    // cout << "\r" << 5 << "% completed.       " << flush;

    int one_primitives[] = {0, 1, 1, 1, 1, 3, 3, 3, 3, 0, 4, 0};
    int two_primitives[] = {0, 4, 4, 4, 0, 2, 2, 2, 4, 3, 4, 2};

    int one_x = 0;
    int one_y = 0;
    int two_x = 4;
    int two_y = 4;


    for (int i = 0; i<13; i++) {
        int grid[5][5];

        for (int i = 0; i<5; i++) {
            for (int j = 0; j<5; j++) {
                grid[i][j] = -1;
            }
        }

        grid[one_x][one_y] = 1;
        grid[two_x][two_y] = 2;

        // cout << "\r";
        for (int i = 4; i>=0; i--) {
            for (int j = 0; j< 5; j++) {
                // grid[i][j] = -1;
                if (grid[j][i] == 1) cout << "1 ";
                else if (grid[j][i] == 2) cout << "2 ";
                else cout << "X ";
            }
            cout << endl;
        }
        cout << endl;
        
        if (i == 12) break;
        switch (one_primitives[i])
        {
        case 1:
            one_x++;
            break;

        case 2:
            one_x--;
            break;
    
        case 3:
            one_y++;
            break;

        case 4:
            one_y--;
            break;
        
        default:
            break;
        }

        switch (two_primitives[i])
        {
        case 1:
            two_x++;
            break;

        case 2:
            two_x--;
            break;
    
        case 3:
            two_y++;
            break;

        case 4:
            two_y--;
            break;
        
        default:
            break;
        }
        
        sleep(1);
    }
        sleep(2);
    return 0;
}