#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <windows.h>
#define N 26
using namespace std;

struct Node
{
    Node* child[N];
    bool end_of_word;
    string meaning;

    Node()
    {
        for (int i = 0; i < N; ++i)
            child[i] = NULL;
        end_of_word = false;
    }
};

class Trie
{
private:
    Node* root;

public:
    Trie();
    ~Trie();

    bool read(const string& filename);
    void display();
    bool addWord(const string& word, const string& meaning);
    string search(const string& word);
    bool deleteWord(const string& word);
    bool findWordsWithPrefix(const string& prefix);
    void scramble(int length);
    void guess(const string &word);
    int permute(string& a,int l,int r);
private:
    void insert(const string& word, const string& meaning);
    void clear(Node* node);
    void view(Node* node, const string& prefix);
    bool remove(Node* node, const string& word, int depth);
    bool isLeafNode(Node* node);
    bool isNonEmptyNode(Node* node);
    string toLower(const string& str);
};

void generateCaptcha(char captcha[], int length);
