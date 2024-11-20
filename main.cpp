#include "header.h"
using namespace std;

int main()
{
    srand(time(NULL));

    int captcha_length = 5;
    char captcha[captcha_length + 1];
    generateCaptcha(captcha, captcha_length);

    cout << "CAPTCHA: " << captcha << endl;

    char user_input[captcha_length + 1];
    cout << "Enter CAPTCHA: ";
    cin >> user_input;

    if (strcmp(captcha, user_input) == 0)
    {
        cout << "\033[2J\033[1;1H";
        Trie dictionary;
        string filename = "dictionary.txt";

        if (!dictionary.read(filename))
        {
            cerr << "Failed to read dictionary." << endl;
            return 1;
        }

        int choice,flag=1;
        string word, meaning;

        cout << "DSA Package done by 23PT11 & 23PT37 under the guidance of Dr.G.Poonthalir ma'am\n";
        cout << "\n\t\t\tDICTIONARY IMPLEMENTATION\n";

        while (flag)
        {
            cout << "\nEnter your choice\n1. View\n2. Add\n3. Search\n4. Delete\n5. Find Words with Prefix\n6. Random Words\n0. Exit\n";
            cin >> choice;

            switch (choice)
            {
                case 0:
                    flag=0;
                    cout << "Exiting ..." << endl;
                    Beep(500,700);
                    cout << "\033[2J\033[1;1H";
                    return 0;

                case 1:
                    dictionary.display();
                    break;

                case 2:
                    cout << "Enter the word to add: ";
                    cin >> word;
                    cout << "Enter the meaning: ";
                    cin.ignore();
                    getline(cin, meaning);
                    if (dictionary.addWord(word, meaning))
                    {
                        cout << "Word added successfully." << endl;
                    }
                    else
                    {
                        cerr << "Failed to add word." << endl;
                    }
                    break;

                case 3:
                    cout << "Enter the word to search: ";
                    cin >> word;
                    meaning = dictionary.search(word);
                    if (!meaning.empty())
                    {
                        cout << "Meaning: " << meaning << endl;
                    }
                    else
                    {
                        cerr << "Word not found." << endl;
                    }
                    break;

                case 4:
                    cout << "Enter the word to delete: ";
                    cin >> word;
                    if (!dictionary.deleteWord(word))
                    {
                        cout << "Word deleted successfully." << endl;
                    }
                    else
                    {
                        cerr << "Failed to delete word." << endl;
                    }
                    break;

                case 5:
                    cout << "Enter the prefix to search: ";
                    cin >> word;
                    cout << "Words with the prefix " << word << ":" ;
                    if (!dictionary.findWordsWithPrefix(word))
                    {
                        cerr << " NULL \nNo words found with the prefix " << word << endl;
                    }
                    break;
               case 6:
                    int length;
                    cout << "Enter the length of the word: ";
                    cin >> length;
                    dictionary.scramble(length);
                    break;

                default:
                    cout << "Enter a valid option." << endl;
            }
        }
    }
    else
    {
        cout << "CAPTCHA incorrect. MICROBOT DETECTED.\n";
        Beep(800,800);
        cout << "\033[2J\033[1;1H";
    }

    return 0;
}
