#include "header.h"
#include <fstream>
#include <cstring>
#include <iomanip>
#include<ctime>
#include<cstdlib>
using namespace std;

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    clear(root);
}

bool Trie::read(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "File not found!" << endl;
        return false;
    }

    string word, meaning;
    while (file >> word)
    {
        getline(file, meaning);
        insert(word, meaning);
    }
    file.close();
    return true;
}

void Trie::display()
{
    view(root, "");
}

bool Trie::addWord(const string& word, const string& meaning)
{
    insert(word, meaning);
    ofstream file("dictionary.txt", ios::app);
    if (file.is_open())
    {
        file << "\n" << word << " " << meaning;
        file.close();
        return true;
    }
    else
    {
        cerr << "Failed to open dictionary file for appending!" << endl;
        return false;
    }
}

string Trie::search(const string& word)
{
    string lowerWord = toLower(word);
    Node* current = root;
    for (int i = 0; i < lowerWord.length(); ++i)
    {
        char c = lowerWord[i];
        int index = c - 'a';
        if (!current->child[index])
            return "";
        current = current->child[index];
    }
    if (current && current->end_of_word)
        return current->meaning;
    else
        return "";
}

bool Trie::findWordsWithPrefix(const string& prefix)
{
    string lowerPrefix = toLower(prefix);
    Node* current = root;
    for (char c : lowerPrefix)
    {
        int index = c - 'a';
        if (!current->child[index])
            return false;
        current = current->child[index];
    }
    cout << endl;
    view(current, prefix);
    return true;
}

bool Trie::deleteWord(const string& word)
{
    if (remove(root, word, 0))
    {
        return true;
    }
    return false;
}

void Trie::insert(const string& word, const string& meaning)
{
    string lowerWord = toLower(word);
    Node* current = root;
    for (char c : lowerWord)
    {
        int index = c - 'a';
        if (!current->child[index])
            current->child[index] = new Node();
        current = current->child[index];
    }
    current->end_of_word = true;
    current->meaning = meaning;
}

void Trie::clear(Node* node)
{
    if (!node)
        return;
    for (int i = 0; i < 26; ++i)
        clear(node->child[i]);
    delete node;
}

void Trie::view(Node* node, const string& prefix)
{
    if (!node)
        return;
    if (node->end_of_word)
        cout << setw(21) << left << prefix <<" -" << node->meaning << endl;
    for (int i = 0; i < 26; ++i)
    {
        string newPrefix = prefix + char('a' + i);
        view(node->child[i], newPrefix);
    }
}

bool Trie::remove(Node* node, const string& word, int depth)
{
    if (!node)
        return false;

    if (depth == word.length())
    {
        if (node->end_of_word)
        {
            node->end_of_word = false;
            return false; // Word found and deleted
        }
        return true; // Word not found
    }

    int index = word[depth] - 'a';
    if (remove(node->child[index], word, depth + 1))
    {
        delete node->child[index];
        node->child[index] = NULL;
        return isNonEmptyNode(node) && !node->end_of_word;
    }
    return false;
}

bool Trie::isLeafNode(Node* node)
{
    for (int i = 0; i < 26; ++i)
    {
        if (node->child[i])
            return false;
    }
    return true;
}

bool Trie::isNonEmptyNode(Node* node)
{
    for (int i = 0; i < 26; ++i)
    {
        if (node->child[i])
            return true;
    }
    return false;
}

string Trie::toLower(const string& str)
{
    string lowerStr = str;
    for (char& c : lowerStr)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c += ('a' - 'A');
        }
    }
    return lowerStr;
}
int Trie::permute(string& a,int l,int r)
{
    if (l == r)
    {
        string word = search(a);
        if (word != "")
        {
            cout << "Permutation found: " << a << " - Meaning: " << word << endl;
        }
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(a[l], a[i]);
            permute(a, l + 1, r);
            swap(a[l], a[i]);
        }
    }
    return 0;
}
void Trie::guess(const string &word) {
    if (word.length() < 3) {
        cout << "Invalid length... Try a greater value (min 3 chars)" << endl;
        return;
    }

    const int chances = 3;
    string scrambledWord = word; // Copy the original word to scramble
    cout << "The scrambled word is: " << scrambledWord << endl;
    int flag1 = 1;

    for (int i = 0; i < chances; i++) {
        string guessing;
        cout << "Enter guess " << i + 1 << ": ";
        cin >> guessing;

        // Check if the guessed word is in the dictionary and is a valid substring of the scrambled word
        if (search(guessing) != "" && scrambledWord.find(guessing) != string::npos) {
            cout << "CONGRATULATIONS! Correct guess" << endl;
            flag1 = 0;
            break;
        } else {
            cout << "Wrong guess" << endl;
        }
    }

    if (flag1) {
        cout << "You have exhausted all attempts. Better luck next time!" << endl;
    }
}


void Trie::scramble(int length)
    {
        if(length<3)
                guess("");
        else
        {
            string vowels="aeiou";
            string alpha="abcdefghijklmnopqrstuvwxyz";
            string randomWord="";
            int i=rand()%5;
            int j;
            randomWord+=vowels[i];
            for(int i=0;i<length-1;i++)
            {
                j=rand()%26;
                randomWord+=alpha[j];
            }
            guess(randomWord);
        }
    }

void generateCaptcha(char captcha[], int length)
 {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-+=[]{}|;:,.<>?";

    for (int i = 0; i < length; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        captcha[i] = charset[index];
    }
    captcha[length] = '\0';
}

