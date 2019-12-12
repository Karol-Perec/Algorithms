#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main() {
    ifstream file("/home/karol/CLionProjects/Kodowanie/mickiewicz.txt");
    map<char,int> chars;

    if (!file.is_open()) {
        std::cerr << "Can open file";
        exit(-1);
    } else {
        char oneChar;
        while (!file.eof()) {
            file >> oneChar;
            if (!chars.count(oneChar))
                chars.insert({oneChar,0});
            chars[oneChar]++;
        }


    }

    for (auto i : chars)
        cout << i.first << "-" << i.second << endl;

    file.close();
    return 0;
}