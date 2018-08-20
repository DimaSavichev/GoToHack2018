#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

bool compare (map <string, string> &mas, string word, vector <string> &keys, string &key) {
    bool check = false;
    if (mas.find(word) != mas.end()) {
        key = word;
        return true;
    } else {
        for (int i = 0; i < keys.size(); i++) {
            if (keys[i].find(word) == 0) {
                key = keys[i];
                return true;
            }
        }
        return false;
    }
}

int main(int argc, char * argv[]) {
    bool check;
    string s(argv[1]), z, word, key, ans;
    vector<pair<string, string >> answer;
    vector<string> keys;
    int pass_length;
    cin >> s;
    map<string, string> mas;
    ifstream fout("english.txt");
    for (int i = 0; i < 3000; i++) {
        string str1, str2;
        fout >> str1 >> str2;
        mas.insert(make_pair(str1, str2));
        keys.push_back(str1);
    }
    pass_length = s.size();
    z = s;
    check = false;
    while (!check) {
        pass_length--;
        if (pass_length == -1) {
            if (answer.empty()) {
                check = true;
            } else {
                z = answer[answer.size() - 1].first + z;
                pass_length = answer[answer.size() - 1].first.size() - 1;
                answer.erase(answer.begin() + answer.size() - 1);
            }
        } else {
            word = z.substr(0, pass_length + 1);
            if (compare(mas, word, keys, key)) {
                if (pass_length != z.size() - 1) {
                    z.erase(0, word.size());
                    pass_length = z.size();
                    answer.push_back(make_pair(word, mas[key]));
                } else {
                    check = true;
                    answer.push_back(make_pair(word, mas[key]));
                }
            }
        }
    }
    if (!answer.empty()) {
        for (int i = 0; i < answer.size(); i++) {
            ans = ans + answer[i].second + " ";
        }
        cout << ans;
    } else {
        cout << "Words not found";
    }
    return 0;
}