#include "besenica.h"

using namespace std;

int rng(const int setWordLength)
{
    srand(time(0));
    int num;

    switch (setWordLength)
    {
        case 3: num = (rand() % 10); break;
        case 4: num = (rand() % 10) + 10; break;
        case 5: num = (rand() % 10) + 20; break;
        case 6: num = (rand() % 10) + 30; break;
        case 7: num = (rand() % 10) + 40; break;
        case 8: num = (rand() % 10) + 50; break;
        case 9: num = (rand() % 10) + 60; break;
        case 10: num = (rand() % 10) + 70; break;
    }

    //Picks a random number (0,9), then adds (10, 20,... 70), depending on the wordLength set by the user, to match the required length in the file "wordlist.txt".
    //Number is used to select a 'random' word.


    return num;
}

string generateInput(const int wordLength)
//Reads random word from wordlist.txt
{
    ifstream line ("wordlist.txt");
    string input;
    int i = 0, rnum = rng(wordLength);
    while (line >> input)
    {
        if (i == rnum)
        {
            return input;
        }
        i++;
    }
}

void StartNewGame(int errorMax, int wordLength)
//Initiates startup of game, including variables, values etc. Contains the main logic behind the game
{
    const int ignoreMAX = 300;
    string input, inputCopy;
    char letter;
    int guessed = 0, errors = 0;
    bool check = 0;

    input = generateInput(wordLength);
    inputCopy = input;
    cout<<"Random word chosen. \n";

    for (int i=0; i<input.length(); i++)
        {
            inputCopy[i] = '_';
        }

    cout<<inputCopy<<endl<<endl;

    while (guessed < input.length() && errors < errorMax)
    {
        check = 0;
        cout<<"Input letter in small caps: ";
        cin>>letter;
        while (cin.fail() || !(letter>='a' && letter<='z'))
        {
            cin.clear();
            cin.ignore(ignoreMAX, '\n');
            cout<<"Invalid input, expected letter (a,z) \n \n" << "Input letter in small caps: ";
            cin>>letter;
        }

        //Checking whether letter is valid, as in already used, part of the word or not.
        for (int i=0; i<input.length(); i++)
        {
            if (letter == input[i])
            {
                if (letter == inputCopy[i])
                {
                    cout<<"Letter already guessed! \n \n";
                    check = 1;
                }
                else
                {
                    cout<<"You've guessed a letter! \n";
                    inputCopy[i] = letter;
                    guessed++;
                    cout<<inputCopy<<endl<<endl;
                    check = 1;
                }
            }
        }

        if (check == 0)
        {
            errors++;
            cout<<"You've made a mistake! "<<errors<<"/"<<errorMax<<" \n \n";
        }
    }
    if (guessed == input.length())
    {
        char a;
        cout<<"---"<<endl;
        cout<<"You guessed the word: "<<input<<endl;
        cout<<"---"<<endl;
        cout<<endl<<"When you're ready press any key";
        a = getch();
        //getch is used to capture any character (i.e. any key) the user inputs. Captured letter is not used any further.
    }
    if (errors == errorMax)
    {
        char a;
        cout<<"---"<<endl;
        cout<<"You made too many mistakes"<<endl;
        cout<<"Your word was: "<<input<<endl;
        cout<<"---"<<endl;
        cout<<endl<<"When you're ready press any key";
        a = getch();
    }

}

int main()
{
    const int ignoreMAX = 300;
    int errorMax = 5, wordLength = 3;

    STARTMENU:
    system("cls");
    cout<<"What do you want to do?"<<endl;
    cout<<"1. Start new game \n";
    cout<<"2. Settings \n";
    cout<<"3. Exit \n \n";
    cout<<"Input number: ";

    int input;
    cin>>input;

    while (cin.fail() || !(input>=1 && input<=3))
    {
        cin.clear();
        cin.ignore(ignoreMAX, '\n');
        cout<<"Invalid input, expected integer (1,3) \n \n" << "Input number: ";
        cin>>input;
    }

    //Menus
    switch (input)
    {
        case 1: system("cls"); StartNewGame(errorMax, wordLength); goto STARTMENU; break;
        case 2: system("cls");
                cout<<"What do you want to do?"<<endl;
                cout<<"1. Change word length \n";
                cout<<"2. Change count of errors allowed \n \n";
                cout<<"Input number: ";

                int input2;
                cin>>input2;

                while (cin.fail() || !(input2>=1 && input2<=2))
                {
                    cin.clear();
                    cin.ignore(ignoreMAX, '\n');
                    cout<<"Invalid input, expected integer (1,2) \n \n" << "Input number: ";
                    cin>>input2;
                }

                switch (input2)
                {
                    case 1: system("cls");
                            cout<<"Set the word length: ";
                            cin>>wordLength;

                            while (cin.fail() || !(wordLength>=3 && wordLength<=10))
                            {
                                cin.clear();
                                cin.ignore(ignoreMAX, '\n');
                                cout<<"Invalid input, expected integer (3,10) \n \n" << "Input number: ";
                                cin>>wordLength;
                            }
                            cout<<endl;
                            goto STARTMENU;
                            break;
                    case 2: system("cls");
                            cout<<"Set the maximum number of errors: ";
                            cin>>errorMax;

                            while (cin.fail() || !(errorMax>=1 && errorMax<=10))
                            {
                                cin.clear();
                                cin.ignore(ignoreMAX, '\n');
                                cout<<"Invalid input, expected integer (1,10) \n \n" << "Input number: ";
                                cin>>errorMax;
                            }
                            cout<<endl;
                            goto STARTMENU;
                            break;
                }
                break;
        case 3: cout<<"\n---"<<endl;
                cout<<"Exiting game... \n";
                cout<<"--- \n";
                return 0;
    }
}
