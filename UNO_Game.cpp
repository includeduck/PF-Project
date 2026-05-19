#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;

//Color Constants for the console
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;

//Color handling functions for the console
void setColor(int textColor, int bgColor)
{
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void resetColor()
{
    setColor(WHITE, BLACK);
}

int deck[8][15] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
                   {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1},
                   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
                   {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1},
                   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
                   {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1},
                   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
				   {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1} }; //(-1) represents empty space in the deck

// Global Arrays and variables for the game
char playing_deck_colors[108]; int playing_deck_numbers[108];
char playeronehand[106][2] = {{0}}; char playertwohand[106][2] = {{0}};
int turn = 1; int discardpileindex = 0;
int movecount = 0;
char discardPile[105][2] = {{0}};

// Function Prototypes for the game
void initializeDeck(int deck[8][15]);                                                                                    // Wasay
void shuffleDeck(int deck[8][15]);                                                                                       // Shaheer
void dealCards(char playing_deck_colors[108], int playing_deck_numbers[108]);                                            // Wasay
void playTurn(int& turn);                                                                                                // Shaheer
bool isValidPlay(int playerCard, int topCard);                                                                           // Shaheer
void UpdateDiscardPile(int& turn, int playerCard); 							                                             // Shaheer
void handlespecialcards(int specialcardtype);                                                                            // Wasay
void PrintBoard(); 															                                             // Wasay
void saveLoadGameResults(char playeronehand[106][2], char playertwohand[106][2], int& discardpileindex, bool endofgame); // Wasay
bool callUno(char playeronehand[106][2], char playertwohand[106][2], int& turn); 			                             // Shaheer
void drawcard(char playeronehand[106][2], char playertwohand[106][2], int& turn);                                        // Wasay
void turnshift(int& turn);                                                                                               // Shaheer
void printStatement(string s, char card[1][2]);                                                                          // Wasay
void printBlackStatement(string s, char card[1][2]);                                                                     // Wasay
string charjudge(char card[1][2]);                                                                                       // Wasay
string numjudge(char card[1][2]);                                                                                        // Wasay
void Uno();                                                                                                              // Wasay
void menu();                                                                                                             // Wasay
void winner(char playeronehand[106][2], char playertwohand[106][2], int& movecount);                                     // Wasay
void printCardRow(char card[1][2], int row);                                                                             // Wasay
void printBlackCardRow(char card[1][2], int row);                                                                        // Wasay
void shuffleDeck(int discardPile[105][2]);                                                                               // Shaheer
void showdeck(char playing_deck_colors[108], int playing_deck_numbers[108]);                                             // Wasay

int main() 
{
	menu();
    return 0;
}

void menu()
{
    char choice;
    do
    {
        system("cls");
        cout << "<======================>\n";
        cout << "<----Two-Player-UNO---->\n";
        cout << "<======================>\n";
        cout << endl;
        cout << "1. Play\n";
        cout << "2. Exit UNO\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (choice != '1' and choice != '2')
        {
            continue;
        }

        switch (choice)
        {
        case '1':
        	system("cls");
            Uno();
            break;
        case '2':
            cout << "Exiting UNO..." << endl;
            return;
        default:
            cout << "Invalid choice!\n";
            break;
        }
        system("pause");
    }
	while (choice != '2');
}

void Uno()
{
	bool endofgame = false;
	saveLoadGameResults(playeronehand, playertwohand, discardpileindex, endofgame);
	cout << endl;
	shuffleDeck(deck);
    dealCards(playing_deck_colors, playing_deck_numbers);
    //showdeck(playing_deck_colors, playing_deck_numbers);
    while (playeronehand[0][0] != 0 and playertwohand[0][0] != 0)
    {
        PrintBoard();
        cout << endl;
        playTurn(turn);
        system("pause");
        system("cls"); // Clear the console screen after every turn.
	}
	endofgame = true;
	winner(playeronehand, playertwohand, movecount);
	saveLoadGameResults(playeronehand, playertwohand, movecount, endofgame);
}

void winner(char playeronehand[106][2], char playertwohand[106][2], int& movecount)
{
	if (playeronehand[0][0] == 0)
	{
		cout << "Player One wins! The game had a total of " << movecount << " moves!" << endl;
	}
	else if (playertwohand[0][0] == 0)
	{
		cout << "Player Two wins! The game had a total of " << movecount << " moves!" << endl;
	}
}


void initializeDeck(int deck[8][15])
{
    char colors[4] = {'R', 'G', 'Y', 'B'};
    int index = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            // Skip invalid cards (-1 in the deck)
            if (deck[i][j] != -1)
			{
                // Set colors and numbers.
                playing_deck_colors[index] = (j == 13 or j == 14) ? 'W' : colors[i % 4];
                playing_deck_numbers[index] = deck[i][j];
                index++;
            }
        }
    }
}

void shuffleDeck(int deck[8][15]) 
{
    //int shuffled = 0;
    srand(static_cast<unsigned>(time(0)));
    initializeDeck(deck);
    do
    {

        for (int i = 0; i < 100; i++) // Shuffle a thousand times to ensure fully randomized deck
        {
            int j = rand() % 108;
            int k = rand() % 108;
            char temp_color = playing_deck_colors[j];
            playing_deck_colors[j] = playing_deck_colors[k];
            playing_deck_colors[k] = temp_color;
            int temp_number = playing_deck_numbers[j];
            playing_deck_numbers[j] = playing_deck_numbers[k];
            playing_deck_numbers[k] = temp_number;
            //shuffled++;
        }
    } while (playing_deck_numbers[14] == 10 or playing_deck_numbers[14] == 11 or playing_deck_numbers[14] == 12 or playing_deck_numbers[14] == 13 or playing_deck_numbers[14] == 14);
    //cout << "Shuffled: " << shuffled << endl;
}

void shuffleDeck(char discardPile[105][2]) 
{
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 10000; i++)
	{
		int j = rand() % 105;
		int k = rand() % 105;
		char temp_color = discardPile[j][0];
		discardPile[j][0] = discardPile[k][0];
		discardPile[k][0] = temp_color;
		char temp_number = discardPile[j][1];
		discardPile[j][1] = discardPile[k][1];
		discardPile[k][1] = temp_color;
	}
}

void dealCards(char playing_deck_colors[108], int playing_deck_numbers[108])
{
    for (int i = 0; i < 7; i++)
    {
        playeronehand[i][0] = playing_deck_colors[i];      // Color
        playeronehand[i][1] = playing_deck_numbers[i];     // Number
    }

    for (int i = 0; i < 7; i++)
    {
        playertwohand[i][0] = playing_deck_colors[7 + i];  // Color
        playertwohand[i][1] = playing_deck_numbers[7 + i]; // Number
    }
}

void playTurn(int& turn) 
{
    int playerCard;
    bool valid = false;
    int topCardNumber = playing_deck_numbers[14];
    char topCardColor = playing_deck_colors[14];
    bool turnShifted = false; // Tracks if the turn has already shifted
    bool drawed = false;
	string exitchar;

    if (turn == 1)
	{
        // Player 1's turn
        do
        {
            cout << "Enter E to exit or any other key to continue: "; cin >> exitchar;
            if (exitchar == "E" or exitchar == "e")
            {
                cout << "Exiting...";
                exit(0);
            }

            cout << "Player 1, enter your move or enter 0 to draw a card: ";

            bool unocall = callUno(playeronehand, playertwohand, turn);
            if (!unocall)
            {
                cout << "\nUno penalty invoked!" << endl;
                drawcard(playeronehand, playertwohand, turn);
                drawcard(playeronehand, playertwohand, turn);
                turnshift(turn);
            }

            cin >> playerCard;
            if (playerCard < 0 or playerCard > 108)
            {
                cout << "Invalid input. Enter a number  or 0 to draw a card." << endl;
            }
        } while (playerCard < 0 or playerCard > 106);

        while (true)
		{
            if (playerCard == 0)
			{ // Player chooses to draw a card
                drawcard(playeronehand, playertwohand, turn);
                bool canPlay = false; // Prevents Skip, reverse, and drawtwo from causing abnormal effects.
                for (int i = 0; i < 106; i++)
				{
                    if (playeronehand[i][0] != 0 and (isValidPlay(playeronehand[i][1], topCardNumber) or playeronehand[i][0] == topCardColor))
					{
                        canPlay = true;
                        break;
                    }
                }

                if (!canPlay)
				{
                    turnshift(turn);
                    turnShifted = true;
                }
                drawed = true;
                break;
            }

            if (playerCard < 1 or playerCard > 106 or playeronehand[playerCard - 1][0] == 0)
			{
                cout << "Invalid card selection! Try again  or enter 0 to draw a card: ";
                cin >> playerCard;
                continue;
            }

            valid = (isValidPlay(playeronehand[playerCard - 1][1], topCardNumber) or
                     (playeronehand[playerCard - 1][0] == topCardColor));
            char cardColor = playeronehand[playerCard - 1][0];
            if (cardColor == 'W') { valid = true; } // Overrides the bool value if the card is wild 

            if (valid) 
			{
                int specialCardType = playeronehand[playerCard - 1][1]; 
                UpdateDiscardPile(turn, playerCard);

                for (int i = playerCard - 1; i < 105; i++)
				{
                    playeronehand[i][0] = playeronehand[i + 1][0];
                    playeronehand[i][1] = playeronehand[i + 1][1];
                }

                playeronehand[105][0] = 0;
                playeronehand[105][1] = 0;

                if (specialCardType >= 10 and specialCardType <= 14)
				{
                    handlespecialcards(specialCardType);
                }
                break;
            }
			else
			{
                cout << "Invalid card! Try again  or enter 0 to draw a card: ";
                cin >> playerCard;
            }
        }
    }
	else if (turn == 2) 
	{
        // Player 2's turn 
        do
		{
			cout << "Enter E to exit, or any other key to continue the game: "; cin >> exitchar;
			if (exitchar == "E" or exitchar == "e")
            {
            	cout << "Exiting...";
				exit(0);
			}

            cout << "Player 2, enter your move  or enter 0 to draw a card: ";

            bool unocall = callUno(playeronehand, playertwohand, turn);
            if (!unocall)
            {
				cout << "\nUno penalty invoked!" << endl;
				drawcard(playeronehand, playertwohand, turn);
				drawcard(playeronehand, playertwohand, turn);
				turnshift(turn);
			}

            cin >> playerCard;
            if (playerCard < 0 or playerCard > 106)
			{
                cout << "Invalid input. Enter a number between  or 0 to draw a card." << endl;
            }
        }
		while (playerCard < 0 or playerCard > 106);

        while (true)
		{
            if (playerCard == 0)
			{ // Player chooses to draw a card
                drawcard(playeronehand, playertwohand, turn);
                bool canPlay = false; // Prevents Skip, reverse, and drawtwo from causing abnormal effects.
                for (int i = 0; i < 106; i++)
				{
                    if (playertwohand[i][0] != 0 and (isValidPlay(playertwohand[i][1], topCardNumber) or playertwohand[i][0] == topCardColor))
					{
                        canPlay = true;
                        break;
                    }
                }

                if (!canPlay)
				{
                    turnshift(turn);
                    turnShifted = true;
                }
                drawed = true;
                break;
            }

            if (playerCard < 1 or playerCard > 106 or playertwohand[playerCard - 1][0] == 0)
			{
                cout << "Invalid card selection! Try again or enter 0 to draw a card: ";
                cin >> playerCard;
                continue;
            }

            valid = (isValidPlay(playertwohand[playerCard - 1][1], topCardNumber) or
                     (playertwohand[playerCard - 1][0] == topCardColor));
            char cardColor = playertwohand[playerCard - 1][0];
            if (cardColor == 'W') { valid = true; } // Overrides the bool value if the card is wild

            if (valid)
			{
                int specialCardType = playertwohand[playerCard - 1][1];
                UpdateDiscardPile(turn, playerCard);

                for (int i = playerCard - 1; i < 105; i++)
				{
                    playertwohand[i][0] = playertwohand[i + 1][0];
                    playertwohand[i][1] = playertwohand[i + 1][1];
                }

                playertwohand[105][0] = 0;
                playertwohand[105][1] = 0;

                if (specialCardType >= 10 and specialCardType <= 14)
				{
                    handlespecialcards(specialCardType);
                }
                break;
            }
			else
			{
                cout << "Invalid card! Try again or enter 0 to draw a card: ";
                cin >> playerCard;
            }
        }
    }

    if (!turnShifted) { turnshift(turn); }
    if (!drawed) { discardpileindex++; }
    movecount++;
}

bool isValidPlay(int playerCard, int topCard) 
{
	bool valid = (playerCard == topCard);
    if (topCard == 13 or topCard == 14)
	{
        valid = true;
	}
	return valid;
}

void printStatement(string s, char card[1][2]) // Prints a string with a colored background
{
    if (card[0][0] == 'R') { setColor(BLACK, RED); };
    if (card[0][0] == 'G') { setColor(BLACK, GREEN); }
    if (card[0][0] == 'B') { setColor(WHITE, BLUE); }
    if (card[0][0] == 'Y') { setColor(BLACK, YELLOW); }
    if (card[0][0] == 'W') { setColor(BLACK, WHITE); }
    cout << s;
    resetColor();
}

void printBlackStatement(string s, char card[1][2])
{
	if (card[0][0] == 0) {setColor(WHITE, BLACK);}
	cout << s;
	resetColor();
}

string charjudge(char card[1][2]) // This 'changes' the type from char to string
{
    string chr;
    char character = card[0][0];
    switch (character)
    {
        case 'R': chr = "R"; break;
        case 'G': chr = "G"; break;
        case 'B': chr = "B"; break;
        case 'Y': chr = "Y"; break;
        case 'W': chr = "W"; break;
    }
    return chr;
}

string numjudge(char card[1][2]) // This 'changes' the type from int to string
{
    string chr;
    char number = card[0][1];
    switch (number)
    {
        case 0: chr = "0"; break;
        case 1: chr = "1"; break;
        case 2: chr = "2"; break;
        case 3: chr = "3"; break;
        case 4: chr = "4"; break;
        case 5: chr = "5"; break;
        case 6: chr = "6"; break;
        case 7: chr = "7"; break;
        case 8: chr = "8"; break;
        case 9: chr = "9"; break;
    }
    return chr;
}

void drawcard(char playeronehand[106][2], char playertwohand[106][2], int& turn)
{
	int count1 = 0 , count2 = 0;

	for (int i = 0; i < 106; i++)
	{
		if (playeronehand[i][0] != 0)
		{
			count1++;
		}
	}
	for (int i = 0; i < 106; i++)
	{
		if (playertwohand[i][0] != 0)
		{
			count2++;
		}
	}

	int totalcards = count1 + count2 + 1;
	if (totalcards == 108)
	{
		cout << "Cannot Draw more Cards as the card count is 108 Currently. " << endl;
		return;
	}

    static int nextCardIndex = 15; // Start after initial cards have been dealt

    if (nextCardIndex >= 108)
	{
        cout << "The deck is out of cards!" << endl;
        char topCardColor = playing_deck_colors[14];
        int topCardNumber = playing_deck_numbers[14];
        shuffleDeck(discardPile);
        int discardCount = 0;
        for (int i = 0; i < discardpileindex; i++)
		{
            if (discardPile[i][0] != 0)
			{
                playing_deck_colors[discardCount] = discardPile[i][0];
                playing_deck_numbers[discardCount] = discardPile[i][1];
                discardCount++;
            }
        }
        playing_deck_colors[14] = topCardColor;
        playing_deck_numbers[14] = topCardNumber;
        cout << "Deck repopulated and shuffled!" << endl;
        nextCardIndex = discardCount;
        return;
	}
    if (turn == 1)
    {
        int cardCount = 0;
        while (cardCount < 106 and playeronehand[cardCount][0] != 0)
        {
            cardCount++;
        }

        if (cardCount >= 106)
        {
            cout << "Player One's hand is full." << endl;
            turnshift(turn);
        }
        else
        {
            playeronehand[cardCount][0] = playing_deck_colors[nextCardIndex];
            playeronehand[cardCount][1] = playing_deck_numbers[nextCardIndex];
            nextCardIndex++;
            cout << "Player One drew a card." << endl;
        }
    }
    else if (turn == 2)
    {
        int cardCount = 0;
        while (cardCount < 106 and playertwohand[cardCount][0] != 0)
        {
            cardCount++;
        }
        if (cardCount >= 106)
        {
            cout << "Player Two's hand is full." << endl;
            turnshift(turn);
        }
        else
        {
            playertwohand[cardCount][0] = playing_deck_colors[nextCardIndex];
            playertwohand[cardCount][1] = playing_deck_numbers[nextCardIndex];
            nextCardIndex++;
            cout << "Player Two drew a card." << endl;
        }
    }


}

void UpdateDiscardPile(int& turn, int playerCard)
{
    if (turn == 1)
 	{
        discardPile[discardpileindex][0] = playeronehand[playerCard - 1][0];
        discardPile[discardpileindex][1] = playeronehand[playerCard - 1][1];
    }
	else if (turn == 2)
	{
        discardPile[discardpileindex][0] = playertwohand[playerCard - 1][0];
        discardPile[discardpileindex][1] = playertwohand[playerCard - 1][1];
    }

    playing_deck_colors[14] = discardPile[discardpileindex][0];
	playing_deck_numbers[14] = discardPile[discardpileindex][1];
}

void handlespecialcards(int specialcardtype)
{
    if (specialcardtype == 10)
    { // Skip
        cout << "Special card: Skip! The opponent loses their turn!" << endl;
        turnshift(turn);
    }
    else if (specialcardtype == 11)
    { // Reverse
        cout << "Special card: Reverse! The opponent loses their turn!" << endl;
        turnshift(turn);
    }
    else if (specialcardtype == 12)
    { // Draw Two
        cout << "Special card: Draw Two! The opponent draws two cards!" << endl;
        turnshift(turn);
        drawcard(playeronehand, playertwohand, turn);
        drawcard(playeronehand, playertwohand, turn);
    }
    else if (specialcardtype == 14)
    { // Wild
        char chosenColor;
        do
		{
	        cout << "Special card: Wild! Choose a new color (R, G, B, Y): ";
	        cin >> chosenColor;
	        if (chosenColor != 'R' and chosenColor != 'G' and chosenColor != 'B' and chosenColor != 'Y')
	        {
	        	cout << "Invalid. Chosen Color can only be either Red, Green, Blue, or Yellow!" << endl;
			}
    	}
		while (chosenColor != 'R' and chosenColor != 'G' and chosenColor != 'B' and chosenColor != 'Y');
        playing_deck_colors[14] = chosenColor;
        cout << "The new color is: " << playing_deck_colors[14] << endl;
    }
    else if (specialcardtype == 13)
    { // Wild Draw Four
        char chosenColor;
        do
		{
	        cout << "Special card: Wild Draw Four! Choose a new color (R, G, B, Y): ";
	        cin >> chosenColor;
	        if (chosenColor != 'R' and chosenColor != 'G' and chosenColor != 'B' and chosenColor != 'Y')
	        {
	        	cout << "Invalid. Chosen Color can only be either Red, Green, Blue, or Yellow!" << endl;
			}
    	}
		while (chosenColor != 'R' and chosenColor != 'G' and chosenColor != 'B' and chosenColor != 'Y');
        playing_deck_colors[14] = chosenColor;
        cout << "The new color is: " << playing_deck_colors[14] << endl;
        cout << "The opponent draws four cards." << endl;
		turnshift(turn);
        for (int i = 0; i < 4; i++)
        {
        	drawcard(playeronehand, playertwohand, turn);
		}
    }
}

void turnshift(int& turn) // For easier turn shifting in game 
{
    if (turn == 1)
    {
    	turn = 2;
	}
	else if (turn == 2)
	{
		turn = 1;
	}
}


void PrintBoard()
{
    cout << "Player One's Hand:" << endl;
    for (int i = 0; i < 106; i += 20)
    {
        for (int row = 0; row < 6; row++)
        {
        	int j;
            for (j = i; j < i + 20 and j < 106; j++) 
            {
                if (playeronehand[j][0] != 0)
				{
                    if (row == 5)
                    {
                        if (j < 9)
                        {
                            cout << " Card 0" << j + 1;
                        }
                        else
                        {
                        	if (j > 99) cout << " Card" << j + 1;
                            else cout << " Card " << j + 1;
                        }
                    }
                    else
                    {
                        cout << " ";
                    }
                    char card[1][2] = {{playeronehand[j][0], playeronehand[j][1]}};
                    printCardRow(card, row);
				}
				else
				{
					if (row == 5)
                    {
                        if (j < 9)
                        {
                            cout << " Card 0" << j + 1;
                        }
                        else
                        {
                        	if (j > 99) cout << " Card" << j + 1;
                            else cout << " Card " << j + 1;;
                        }
                    }
                    else
                    {
                        cout << " ";
                    }
                    char card[1][2] = {{playeronehand[j][0], playeronehand[j][1]}};
                    printBlackCardRow(card, row);
				}
            }
            cout << endl;
        }
    }

    cout << endl;
    cout << "Top Card: " << endl;
    char topcard[1][2];
    topcard[0][0] = playing_deck_colors[14];
    topcard[0][1] = playing_deck_numbers[14];
    for (int row = 0; row < 5; row++)
    {
        printCardRow(topcard, row);
        cout << endl;
    }
    cout << endl;

    cout << "Player Two's Hand:" << endl;
    for (int i = 0; i < 106; i += 20)
    {
        for (int row = 0; row < 6; row++)
        {
        	int j;
            for (j = i; j < i + 20 and j < 106; j++)
            {
                if (playertwohand[j][0] != 0)
                {
                    if (row == 5)
                    {
                        if (j < 9)
                        {
                            cout << " Card 0" << j + 1;
                        }
                        else
                        {
                        	if (j > 99) cout << " Card" << j + 1;
                            else cout << " Card " << j + 1;
                        }
                    }
                    else
                    {
                        cout << " ";
                    }
                    char card[1][2] = {{playertwohand[j][0], playertwohand[j][1]}};
                    printCardRow(card, row);
                }
                else
                {
                	if (row == 5)
                    {
                        if (j < 9)
                        {
                            cout << " Card 0" << j + 1;
                        }
                        else
                        {
                        	if (j > 99) cout << " Card" << j + 1;
                            else cout << " Card " << j + 1;
                        }
                    }
                    else
                    {
                        cout << " ";
                    }
                    char card[1][2] = {{playertwohand[j][0], playertwohand[j][1]}};
                    printBlackCardRow(card, row);
				}
            }
            cout << endl;
        }
    }
}

void printCardRow(char card[1][2], int row) // Chooses which part of the card to print based on the row number.
{
    switch (row)
	{
        case 0:
            printStatement("-------", card); // I'm beginning to feel like a Rap God, Rap God, 
            break;
        case 1:
            printStatement("---", card);
            printStatement(charjudge(card), card);
            printStatement("---", card);
            break;
        case 2:
            printStatement("-------", card);
            break;
        case 3:
            printStatement("---", card);
            if (static_cast<int>(card[0][1]) == 10)
			{
                printStatement("S---", card); // Skip
            }
			else if (static_cast<int>(card[0][1]) == 11)
			{
                printStatement("R---", card); // Reverse
            }
			else if (static_cast<int>(card[0][1]) == 12)
			{
                printStatement("DT--", card); // Draw Two
            }
			else if (static_cast<int>(card[0][1]) == 13)
			{
                printStatement("DF--", card); // Draw Four
            }
			else if (static_cast<int>(card[0][1]) == 14)
			{
                printStatement("W---", card); // Wild
            }
			else
			{
                printStatement(numjudge(card), card);
                printStatement("---", card);
            }
            break;
        case 4:
            printStatement("-------", card);
            break;
    }
}

void printBlackCardRow(char card[1][2], int row)
{
	switch (row)
	{
        case 0:
        case 1:
        case 2:
        case 3:
        case 4: printBlackStatement("-------", card); break;
    }
}

void saveLoadGameResults(char playeronehand[106][2], char playertwohand[106][2], int& movecount, bool endofgame)
{
	if (endofgame)
	{
	    string winner;
	    if (playeronehand[0][0] == 0)
		{
	        winner = "Player One Wins! The game had a total of " + to_string(movecount) + " moves!";
	    }
		else if (playertwohand[0][0] == 0)
		{
	        winner = "Player Two Wins! The game had a total of " + to_string(movecount) + " moves!";
	    }
	    ofstream outFile("GameResults.txt");
	    if (outFile.is_open())
		{
	        outFile << winner << endl;
	        outFile.close();
	        cout << "Game results saved successfully!" << endl;
	    }
		else
		{
	        cerr << "Can't Open File" << endl;
	    }
	}

	else if (!endofgame)
	{
		cout << "Previous Game Result: " << endl;
	    ifstream inFile("GameResults.txt");
	    if (inFile.is_open())
		{
	        string gameResult;
	        while (getline(inFile, gameResult))
			{
	            cout << gameResult << endl;
	        }
	        inFile.close();
	    }
		else
		{
	        cerr << "Can't Open File" << endl;
	    }
	}
}

bool callUno(char playeronehand[106][2], char playertwohand[106][2], int& turn)
{
    bool unocall = false;
    string calluno;
    int cardCount = 0;
    if (turn == 1)
    {
        for (int i = 0; i < 106; i++)
        {
            if (playeronehand[i][0] != 0)
            {
                cardCount++;
            }
        }
        if (cardCount == 2)
        {
        	cout << endl;
            cout << "Two cards left for Player One: ";
			cin >> calluno;
            if (calluno == "UNO" or calluno == "UNo" or calluno == "UnO" or calluno == "Uno" or calluno == "uNO" or calluno == "uNo" or calluno == "unO" or calluno == "uno")
            {
                unocall = true;
            }
        }
        else
        {
            unocall = true;
        }
    }
    else if (turn == 2)
    {
        for (int i = 0; i < 106; i++)
        {
            if (playertwohand[i][0] != 0)
            {
                cardCount++;
            }
        }
        if (cardCount == 2)
        {
        	cout << endl;
            cout << "Two cards left for Player Two: ";
			cin >> calluno;
            if (calluno == "UNO" or calluno == "UNo" or calluno == "UnO" or calluno == "Uno" or calluno == "uNO" or calluno == "uNo" or calluno == "unO" or calluno == "uno")
            {
                unocall = true;
            }
		}
        else
        {
            unocall = true;
        }
    }
    return unocall;
}

void showdeck(char playing_deck_colors[108], int playing_deck_numbers[108]) // For debugging purposes
{
	for (int i = 0; i < 108; i++)
	{
		cout << i << ": "<< "Color: " << playing_deck_colors[i] << " Number: " << playing_deck_numbers[i] << endl;
	}
}
