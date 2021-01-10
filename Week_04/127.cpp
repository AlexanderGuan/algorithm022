/*127 单词接龙  */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        unordered_map<string, int> visit_map;
        queue<string> que;

        if (wordSet.find(endWord) == wordSet.end()) return 0;

        que.push(beginWord);
        wordSet.erase(beginWord);
        visit_map.insert(pair<string, int>(beginWord, 1));

        while (!que.empty()) {
            string word = que.front();
            que.pop();
            int path = visit_map[word];
            for (int i = 0; i < word.size(); ++i) {
                string new_word = word;
                for (int j = 'a'; j <= 'z'; ++j) {
                    new_word[i] = j;
                    if (new_word == endWord) return path + 1;
                    if (wordSet.find(new_word) != wordSet.end() && visit_map.find(new_word) == visit_map.end()) {
                        visit_map.insert(pair<string, int>(new_word, path + 1));
                        que.push(new_word);
                    }
                }
            }
        }
        return 0;
    }
};

int main() {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};

    Solution sol;
    cout << sol.ladderLength(beginWord, endWord, wordList);

    return 0;
}
