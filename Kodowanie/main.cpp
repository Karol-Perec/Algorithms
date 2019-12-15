#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>

using namespace std;

struct Node {
    char character;
    int amount;
    struct Node *left;
    struct Node *right;
};

struct NodeCmp {
    bool operator()(const Node &lhs, const Node &rhs) const {
        return lhs.amount <= rhs.amount;
    }
};

void insertCodingRule(std::map<char, string> &codingTable, Node *node, const string &code) {
    if (node != nullptr) {
        if (node->character) {
            codingTable.insert({node->character, code});
        } else {
            insertCodingRule(codingTable, node->left, code + "0");
            insertCodingRule(codingTable, node->right, code + "1");
        }
    }
}

int main() {
    ifstream file("../witcher.txt");
    map<char, int> chars;

///wczytanie i policzenie znaków z pliku
    if (!file.is_open()) {
        std::cerr << "Can open file";
        exit(-1);
    } else {
        char character;
        while (file >> character) {
            if (!chars.count(character))
                chars.insert({character, 0});
            chars[character]++;
        }
    }

///konstrukcja drzewa dekodującego o odpowiedniej strukturze
    std::set<Node, NodeCmp> setOfChars;
    for (auto i : chars) {
        setOfChars.insert(Node{i.first, i.second, nullptr, nullptr});
    }

    while (setOfChars.size() > 1) {
        auto first = setOfChars.begin();
        auto second = setOfChars.begin();
        second++;
        setOfChars.insert(Node{{}, first->amount + second->amount, new Node(*second), new Node(*first)});
        setOfChars.erase(first);
        setOfChars.erase(second);
    }
    auto decodingTree = new Node(*setOfChars.begin());


///konstrukcja tabeli kodującej
    std::map<char, string> codingTable;
    insertCodingRule(codingTable, decodingTree, "");
    for (const auto &i : codingTable)
        cout << i.first << " <-> " << i.second << endl;

///zakoduj do pliku
    ofstream encodedFile("../witcherEncoded.txt", std::ofstream::trunc);
    if (!encodedFile.is_open()) {
        file.close();
        std::cerr << "Can open file";
        exit(-1);
    } else {
        file.clear();
        file.seekg(0);
        char character;
        while (file >> character)
            encodedFile << codingTable[character];
    }

///informacje o kompresji
    file.clear();
    file.seekg(0, ios::end);
    float originalSize = file.tellg();
    float compressedSize = encodedFile.tellp() / 8;
    cout << "Original file size: " << originalSize << " B" << endl;
    cout << "Compressed file size: " << compressedSize << " B" << endl;
    cout << "Compression effectivness: " << ((compressedSize - originalSize) / originalSize) * 100 << "%";

    encodedFile.close();
    file.close();
    return 0;
}