#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>

using namespace std;

int main() {
///dekodowanie
    ifstream codingTableFile("../codingTable.txt");
    codingTableFile >> std::noskipws;
    ifstream encodedFile_("../witcherEncoded.txt");
    ofstream decodedFile("../witcherDecoded2.txt", std::ofstream::trunc);

    char character;
    string code;
    std::map<string, char> codingTable;
    char temp;
    while (!codingTableFile.eof()) {
        codingTableFile >> character;
        codingTableFile >> temp;
        codingTableFile >> code;
        codingTableFile >> temp;
        codingTable.insert({code, character});
    }
    codingTableFile.close();

    for (auto& i : codingTable) {
        cout << i.first << " -> " << i.second << endl;
    }
    codingTable.erase("0");

    if (!encodedFile_.is_open()) {
        std::cerr << "Can open file";
        exit(-1);
    } else {
        char bit;
        string bits{};
        while (encodedFile_ >> bit) {
            bits += bit;
            auto iter = codingTable.find(bits);
            if (iter != codingTable.end())
            {
                decodedFile << iter->second;
                bits = {};
            }
        }
    }

    encodedFile_.close();
    decodedFile.close();

    return 0;
}

