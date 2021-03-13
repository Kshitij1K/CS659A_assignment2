#include <iostream>
#include <fstream>
#include <utility>

using namespace std;
int N = 5;
int R = 2;
int L;

inline int X(int t, int r, int x, int y) {
    return t + r*(L+1) + x*(L+1)*R + y*(L+1)*R*N + 1;
}

int main() {
    std::pair<int, int> start_pos[2] = {{0,0}, {4,4}};
    std::pair<int, int> end_pos[2] = {{4,4}, {0,0}};
    std:pair<int, int> obstacles[6] = {{2,0}, {3,0}, {1,2}, {3,2}, {1,4}, {2,4}};

    cout << "Please enter the value of L \n";
    cin >> L;
    
    string filename;
    cout << "Please enter the name of the file to make the CNF file \n";
    cin >> filename;
    fstream cnf_file;
    cnf_file.open(filename, fstream::out);

    if (cnf_file.is_open()) {
        // Start and end conditions
        for (int r = 0; r < R; r++) {
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    if (x == start_pos[r].first && y == start_pos[r].second) {
                        cnf_file << X(0, r, x, y) << " 0" << endl;
                        
                    } else {
                        cnf_file << "-" << X(0, r, x, y) << " 0" << endl;
                    }

                    if (x == end_pos[r].first && y == end_pos[r].second) {
                        cnf_file << X(L, r, x, y) << " 0" << endl;
                        cout << X(L, r, x, y) << " 0" << endl;
                    } else {
                        cnf_file << "-" << X(L, r, x, y) << " 0" << endl;
                    }
                }
            }
        }
        

        // Movement Constraints
        for (int r = 0; r < R; r++) {
            for (int t = 0; t < L; t++) {
                for (int x = 0; x < N; x++) {
                    for (int y = 0; y < N; y++) {
                        cnf_file << "-" << X(t+1, r, x, y) << " ";
                        cnf_file << X(t, r, x, y) << " ";
                        if (x < N-1) cnf_file << X(t, r, x+1, y) << " ";
                        if (x > 0) cnf_file << X(t, r, x-1, y) << " ";
                        if (y < N-1) cnf_file << X(t, r, x, y+1) << " ";
                        if (y > 0) cnf_file << X(t, r, x, y-1) << " ";
                        cnf_file << "0" << endl;
                    }
                }
            }
        }

        // Obstacle avoidance
        for (int r = 0; r<2; r++) {
            for (int t = 0; t <= L; t++) {
                for (int g = 0; g < 6; g++) {
                    cnf_file << "-" << X(t, r, obstacles[g].first, obstacles[g].second) << " 0" << endl;
                }
            }
        }
        
        // Collision Avoidance
        for (int t = 0; t <= L; t++) {
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    cnf_file << "-" << X(t, 0, x, y) << " -" << X(t, 1, x, y) << " 0" << endl;
                    if (x != N-1) cnf_file << "-" << X(t, 0, x, y) << " -" << X(t, 1, x+1, y) << " -" << X(t+1, 0, x+1, y) << " -" << X(t+1, 1, x, y) << " 0" << endl;
                    if (x != N-1) cnf_file << "-" << X(t, 1, x, y) << " -" << X(t, 0, x+1, y) << " -" << X(t+1, 1, x+1, y) << " -" << X(t+1, 0, x, y) << " 0" << endl;
                    if (y != N-1) cnf_file << "-" << X(t, 0, x, y) << " -" << X(t, 1, x, y+1) << " -" << X(t+1, 0, x, y+1) << " -" << X(t+1, 1, x, y) << " 0" << endl;
                    if (y != N-1) cnf_file << "-" << X(t, 1, x, y) << " -" << X(t, 0, x, y+1) << " -" << X(t+1, 1, x, y+1) << " -" << X(t+1, 0, x, y) << " 0" << endl;
                }
            }
        }

        // Conditions for Soundness
        for (int t = 0; t<=L; t++) {
            for (int xi = 0; xi < N; xi++) {
                for (int yi = 0; yi < N; yi++) {
                    for (int xf = 0; xf < N; xf++) {
                        for (int yf = 0; yf < N; yf++) {
                            if (xi != xf || yi != yf) cnf_file << "-" << X(t,0,xi,yi) << " -" << X(t,0,xf,yf) << " 0" << endl;
                            if (xi != xf || yi != yf) cnf_file << "-" << X(t,1,xi,yi) << " -" << X(t,1,xf,yf) << " 0" << endl;
                        }
                    }
                }
            }
        }

        cnf_file.close();
    }

    else cout << "File cannot be opened/created.";

    // Prints the mappings of variables which can be used for manual inspection
    for (int y = 0; y<N;y++) {
        for (int x = 0; x<N; x++) {
            for (int r=0; r<R; r++) {
                for (int t = 0; t<=L; t++) {
                    cout << "X(" << t << ", " << r << ", " << x << ", " << y <<"): " << X(t, r, x, y) <<endl;
                }
            }
        }
    }

    return 0;
}