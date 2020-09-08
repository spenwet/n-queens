#include <iostream>
#include <string>
using namespace std;

//Use a simple depth-first search to solve the n-queens problem
//That is, place 8 queens on a standard chess board without any being in check with one another

//Define queen struct as her x and y coordinates
struct queens{
    int m_row;
    int m_col;
};

//check diagonal checks with other queens
bool check_diagonals(int r1, int c1, int r2, int c2, int n){
    int r_u = r1;
    int c_u = c1;
    int r_d = r1;
    int c_d = c1;
    while (r_u<n || c_u<n || r_d >= 0 || c_d >=0){
        if ( (r_u == r2 || r_d == r2) && (c_u==c2 || c_d==c2) ){
            return false;
        }
        r_u++;
        r_d--;
        c_u++;
        c_d--;
    }
    return true;
}

//print the board as described in the README
void print_queens(queens q[]){
    string board[8][8];
    for (int b = 0; b<8;b++){
        for (int d = 0; d<8;d++){
            if ((b%2)==0){
                if((d%2)==0){
                    board[b][d] = "O";
                }else{
                    board[b][d] = "X";
                }
            }else{
                if((d%2)==0){
                    board[b][d] = "X";
                }else{
                    board[b][d] = "O";
                }
            }
        }
    }
    for (int i = 0; i<8; i++){
        board[q[i].m_col][q[i].m_row] = "Q";
    }

    for (int x = 0; x<8; x++){
        cout<<" _ _ _ _ _ _ _ _"<<endl;
        cout<<"|";
        for (int y = 0; y<8; y++){
            cout<<board[y][x]<<"|";
        }
        cout<<endl;
    }
    cout<<" _ _ _ _ _ _ _ _"<<endl;
}

//Recursively place a queen, check if the current board state is a valid solution, then call function
//If board state is not valid, try next spot
//If no placement is possible, backtrack
bool place_queens(bool taken_rows[], bool taken_cols[], int placed, queens q[]){
    for (int r = 0; r<=7; r++){
        if (!taken_rows[r]){
            
            for (int c=0; c<=7; c++){
                if (!taken_cols[c]){
                    
                    bool valid = true;
                    
                    for (int i = 0; i<placed && valid; i++){
                        valid = check_diagonals(q[i].m_row, q[i].m_col, r, c, 8);
                    }
                    

                    if(valid){
                        taken_rows[r] = true;
                        taken_cols[c] = true;
                        queens n;
                        n.m_col = c;
                        n.m_row = r;
                        
                        q[placed] = n;
                        placed++;
                        if(placed==8){
                            print_queens(q);
                            return true;
                        }
                        
                        bool rec = place_queens(taken_rows, taken_cols, placed, q);
                        if (!rec){
                            
                            taken_rows[r] = false;
                            taken_cols[c] = false;
                            placed--;
                        } else {
                            return true;
                        }
                    }

                }
            }
        }
    }
    return false;
}


int main(){
    //create blank board
    bool t_rows[8], t_cols[8];
    queens q[8];
    int p = 0;
    for (int i = 0; i<8; i++){
        t_rows[i] = false;
        t_cols[i] = false;
    }

    //Solve
    bool solved = place_queens(t_rows, t_cols, p, q);

    //Print results
    if (solved){
        cout<<"You did it!"<<endl;
    }else{
        cout<< "FAILURE"<<endl;
    }
}