#include <bits/stdc++.h>

using namespace std;

struct Node {
    string key;      
    int bitIndex;   
    Node* left;      
    Node* right;     

    Node(string k, int b) : key(k), bitIndex(b), left(nullptr), right(nullptr) {}
};

class PatriciaTrie {
private:
    Node* root;

   
    int findFirstDifferentBit(const string& s1, const string& s2) {
        int minLength = min(s1.length(), s2.length());
        for (int i = 0; i < minLength * 8; ++i) {
            if (getBit(s1, i) != getBit(s2, i)) {
                return i;
            }
        }
        if (s1.length() != s2.length())
            return minLength * 8;
        return -1;
    }


    bool getBit(const string& str, int index) {
        int charIndex = index / 8;       
        int bitIndex = 7 - (index % 8); 
        if (charIndex >= str.length()) return 0; 
        return (str[charIndex] >> bitIndex) & 1;
    }

public:
    PatriciaTrie() {
        root = new Node("", -1); 
        root->left = root;       
    }

    void insert(const string& key) {
        Node* curr = root;
        Node* next = root->left;


        while (curr->bitIndex < next->bitIndex) {
            curr = next;
            next = getBit(key, curr->bitIndex) ? curr->right : curr->left;
        }


        if (next->key == key) {
            cout  << key << "vekje postoi"<<endl;
            return;
        }


        int newBitIndex = findFirstDifferentBit(key, next->key);


        curr = root;
        Node* parent = root->left;
        while (curr->bitIndex < parent->bitIndex && parent->bitIndex < newBitIndex) {
            curr = parent;
            parent = getBit(key, curr->bitIndex) ? curr->right : curr->left;
        }


        Node* newNode = new Node(key, newBitIndex);
        if (getBit(key, newBitIndex)) {
            newNode->left = parent;
            newNode->right = newNode;
        } 
        else {
            newNode->left = newNode;
            newNode->right = parent;
        }

        if (getBit(key, curr->bitIndex)) {
            curr->right = newNode;
        } 
        else {
            curr->left = newNode;
        }

     
    }

    bool search(const string& key) {
        Node* curr = root;
        Node* next = root->left;


        while (curr->bitIndex < next->bitIndex) {
            curr = next;
            next = getBit(key, curr->bitIndex) ? curr->right : curr->left;
        }

        return next->key == key;
    }
};

int main() {
    PatriciaTrie trie;

    trie.insert("zdr");
    trie.insert("zdravo");
    trie.insert("zdravec");
    trie.insert("zdravko");

    cout << "barame zdravo: ";
    if (trie.search("zdravo"))
        cout << "najdeno" << endl;
    else
        cout << "nema" << endl;

    cout << "barame zdravko: ";
    if (trie.search("zdravko"))
        cout << "najdeno" << endl;
    else
        cout << "nema" << endl;

    cout << "barame zraci: ";
    if (trie.search("zraci"))
        cout << "najdeno" << endl;
    else
        cout << "nema" << endl;

    cout << "barame zdravkica: ";
    if (trie.search("zdravkica"))
        cout << "najdeno" << endl;
    else
        cout << "nema" << endl;

    return 0;
}
