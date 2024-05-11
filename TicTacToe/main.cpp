#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
int table[3][3] = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
};

int tableOptions[11] = { 0, 0, 0,
                         0, 0, 0,           // 0 if that spot on the table is free, 1 if taken
                         0, 0, 0 };

int nr = 0;                                // counts up to 9 to stop the game (max possible choices)


                                           // value 1 stands for computer choice and 2 for user choice

void switch_case(int n, int &x, int &y) {

    switch (n) {

    case 1: {x = 0; y = 0; break; };
    case 2: {x = 0; y = 1; break; };
    case 3: {x = 0; y = 2; break; };
    case 4: {x = 1; y = 0; break; };
    case 5: {x = 1; y = 1; break; };            // converts number from 1-9 to (x,y) coordinates
    case 6: {x = 1; y = 2; break; };
    case 7: {x = 2; y = 0; break; };
    case 8: {x = 2; y = 1; break; };
    case 9: {x = 2; y = 2; break; };
    default: break;
    }
}

int winCondition() {

    int win = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (win == 0 && table[i][j] != 0) {

                if (i == 1 && j == 1) {
                    if ( ( (table[i][j] == table[i-1][j-1]) && (table[i][j] == table[i+1][j+1]) ) || ( (table[i][j] == table[i-1][j+1]) && (table[i+1][j-1] == table[i][j]) ) ) {
                        win = 1;  // win on diagonal
                    }
                    else {
                        if((table[i][j] == table[i-1][j]) &&(table[i][j] == table[i+1][j])){
                            win = 1; // exception for win on vertical when i == j
                        }
                        else{
                            if((table[i][j] == table[i][j-1]) && (table[i][j] == table[i][j+1])){
                                win = 1; // exception for win on horizontal when i == j
                            }
                        }
                    }
                }

                else {
                    if (i == 1) {
                        if ((table[i][j] == table[i-1][j]) && (table[i][j] == table[i+1][j])) {
                            win = 1; // win on vertical
                        }
                    }
                    else {
                        if (j == 1) {
                            if ((table[i][j] == table[i][j-1]) && (table[i][j] == table[i][j+1])) {
                                win = 1; // win on horizontal
                            }
                        }
                    }
                }
            }

        }
    }

    return win;
}


void computerChoice(int &nr) {


        srand((unsigned int)time(0));

        int x = 0, y = 0;
        int random_number = 1 + rand() % 9;

        while (tableOptions[random_number] == 1 && nr!=9) {
            random_number = 1 + rand() % 9;
        }


        switch_case(random_number, x, y);


        if (table[x][y] == 0) {
            table[x][y] = 1;
            tableOptions[random_number] = 1;
            nr++;
            std::cout << "computer picked: " << random_number << "\n\n";
        }
        else {
            std::cout << "game over" << "\n";
        }




}

void userChoice(int &nr) {


        int x = 0, y = 0;
        int n;

        std::cin >> n;
        if ((n < int(1) && n > int(9)) || !std::cin) {
            std::cout << "Your option should be a number between 1 and 9. Try again!\n\n";
            userChoice(nr);
        }
        else {
            switch_case(n, x, y);

            if (table[x][y] != 0) {
                std::cout << "Option already used. Pick again!" << "\n";
                userChoice(nr);
            }
            else {
                table[x][y] = 2;
                tableOptions[n] = 1;
                nr++;
                std::cout << "\nyou picked: " << n << "\n\n";
            }
        }

}

void displayTable() {


        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (table[i][j] == 1) {
                    std::cout << "[X]" << " ";
                }
                else {
                    if (table[i][j] == 2) {
                        std::cout << "[O]" << " ";
                    }
                    else {
                        std::cout << "[ ]" << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
        if (nr == 9 && (winCondition() == 0)) {
            std::cout << "It's a tie! \n";
        }




}

int main()
{

    std::cout << "Welcome to TicTacToe! Rules are simple: you are \"O\" and the computer is \"X\". \n\n";
    std::cout << "(1) (2) (3)\n";
    std::cout << "(4) (5) (6)        <---- This is the board. In order to place your pick, \n";
    std::cout << "(7) (8) (9)              you have to type in the correspondent number from 1 to 9.\n";

    srand((unsigned int)time(0));
    if (rand() % 2 == 0) {
        std::cout << "You pick first!\n\n";
        do {

                userChoice(nr);
                if (winCondition() == 1) {
                    displayTable();
                    std::cout << "WE HAVE A WINNER!\n";
                    break;
                }
                computerChoice(nr);
                if (winCondition() == 1) {
                    displayTable();
                    std::cout << "WE HAVE A WINNER!\n";
                    break;
                }
                displayTable();

        } while (nr < 9 && winCondition() == 0);
     }
    else {
        std::cout << "Computer picks first!\n\n";
        do {


                computerChoice(nr);
                if (winCondition() == 1) {
                    displayTable();
                    std::cout << "WE HAVE A WINNER!\n";
                    break;
                }
                displayTable();
                std::cout << "Enter option: " << "\n";
                userChoice(nr);
                if (winCondition() == 1) {
                    displayTable();
                    std::cout << "WE HAVE A WINNER!\n";
                    break;

                }



        } while (nr < 9 && winCondition() == 0);
    }





    return 0;
}
