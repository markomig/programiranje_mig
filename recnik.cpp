#include <bits/stdc++.h>
#include <fstream>



using namespace std;



typedef wchar_t Char;
typedef wstring String;
typedef wostream Ostream;
#define Cout wcout;
String index_to_char(int i)
{
    const wstring str[31]= {L"\u00d0\u00b0", L"\u00d0\u00b1", L"\u00d0\u00b2", L"\u00d0\u00b3", L"\u00d0\u00b4", L"\u00d1\u0093", L"\u00d0\u00b5", L"\u00d0\u00b6", L"\u00d0\u00b7", L"\u00d1\u0095", L"\u00d0\u00b8", L"\u00d1\u0098", L"\u00d0\u00ba", L"\u00d0\u00bb", L"\u00d1\u0099", L"\u00d0\u00bc", L"\u00d0\u00bd", L"\u00d1\u009a", L"\u00d0\u00be", L"\u00d0\u00bf", L"\u00d1\u0080", L"\u00d1\u0081", L"\u00d1\u0082", L"\u00d1\u009c", L"\u00d1\u0083", L"\u00d1\u0084", L"\u00d1\u0085", L"\u00d1\u0086", L"\u00d1\u0087", L"\u00d1\u009f", L"\u00d1\u0088"};
    return str[i];
}

int char_to_index(wchar_t second)
{
    switch (second)
    {
    case  L'\u00b0':
        return 0;
    case  L'\u00b1':
        return 1;
    case  L'\u00b2':
        return 2;
    case  L'\u00b3':
        return 3;
    case  L'\u00b4':
        return 4;
    case  L'\u0093':
        return 5;
    case  L'\u00b5':
        return 6;
    case  L'\u00b6':
        return 7;
    case  L'\u00b7':
        return 8;
    case  L'\u0095':
        return 9;
    case  L'\u00b8':
        return 10;
    case  L'\u0098':
        return 11;
    case  L'\u00ba':
        return 12;
    case  L'\u00bb':
        return 13;
    case  L'\u0099':
        return 14;
    case  L'\u00bc':
        return 15;
    case  L'\u00bd':
        return 16;
    case  L'\u009a':
        return 17;
    case  L'\u00be':
        return 18;
    case  L'\u00bf':
        return 19;
    case  L'\u0080':
        return 20;
    case  L'\u0081':
        return 21;
    case  L'\u0082':
        return 22;
    case  L'\u009c':
        return 23;
    case  L'\u0083':
        return 24;
    case  L'\u0084':
        return 25;
    case  L'\u0085':
        return 26;
    case  L'\u0086':
        return 27;
    case  L'\u0087':
        return 28;
    case  L'\u009f':
        return 29;
    case  L'\u0088':
        return 30;
    }
}

String transform_string( String S)
{
    String rez;
    for(int i=1;i<S.size();i+=2)
    {
        rez+=S[i];

    }
    return rez;
}





struct TrieNode
{

    TrieNode* children[31]= {0};
    bool endofword;
~TrieNode() {
        for (int i = 0; i < 31; i++) {
            if (children[i] != nullptr)
                delete children[i];
        }
    }

};

class Trie
{
private:
    TrieNode* root;

void deleteNode(TrieNode* node) {
    for (int i = 0; i < 31; ++i) {
        if (node->children[i]) {
            deleteNode(node->children[i]);
        }
    }
    delete node;
}
public:
    Trie()
    {
        root = new TrieNode();
    }

    void Insert(String S)
    {
        S=transform_string(S);
        TrieNode* node= root;
        int index;
        for(int i=0; i<S.size(); i++)
        {
            index= char_to_index(S[i]);
            if(!node->children[index])
            {
                node->children[index]=new TrieNode();
            }
            node=node->children[index];
        }
        if(i+1==S.size())
            node->endofword=true;
    }

    bool Search(String S)
    {
        S=transform_string(S);
          TrieNode* node= root;
        int index;
        for(int i=0; i<S.size(); i++)
        {
            index= char_to_index(S[i]);
            if(!node->children[index])
            {
                return false;
            }
            node=node->children[index];
        }
        return true;
    }






void print(Ostream & out = Cout)
{
    traverse(root,String(),out);
}



    void traverse(TrieNode* node,String str, Ostream & out )
    {
        if(node->endofword)
        {
            out<<str<<endl;
        }
        for(int i=0; i<31; i++)
        {
            if(node->children[i])
            {
                traverse(node->children[i], str+index_to_char(i),out);
            }
        }
    }


    ~Trie() {
    deleteNode(root);
}


};


main()
{

     wifstream in("words.txt");
    wofstream out("result.txt");
    wstring word;
    Trie trie;
    while (in >> word)
    {
        out << word;
        trie.add(word);
        out << " " << trie.exists(word) << " " << trie.exists(word + IndexToLetter(0)) << endl;// 1 0
    }
    out << endl;


    trie.print(out);
    in.close();
    out.close();
    return 0;
}
