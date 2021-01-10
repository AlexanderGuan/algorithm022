/*126 单词接龙II*/
/*标准BFS解法，但是queue中保存的不是word，而是path*/
/*本方法是标准BFS，没有用到任何其他它方法。

本方法中的queue所保存的是路径path( 即queue<vector<string>>)，而不是单词word(即queue<string>)。
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        // 1. 声明
        queue<vector<string>> paths; //BFS队列
        unordered_set<string> word_set(wordList.begin(),wordList.end()); // 将wordList哈希化，方便之后搜索
        unordered_set<string> visited_map;// 访问表，保存已经访问过的word
        vector<vector<string>> res;// 答案集

        // 2. 特判
        if (word_set.find(endWord) == word_set.end()) return {};

        // 3. 初始化
        paths.push({beginWord});
        visited_map.insert(beginWord);
        int level = 1; // 深度/层数/步数
        int min_level = INT_MAX;// 路径最短答案的深度

        // 4. 开始搜索
        while (!paths.empty()){
            vector<string> path = paths.front();
            paths.pop();
            // 当前路径的size大于level时，说明广搜进入了下一层
            if (path.size() > level){
                // 删除上一层所访问过的word，因为这些word在本层及之后的层不会再被访问
                for(const string& word:visited_map){
                    word_set.erase(word);
                }
                // 清空visited列表
                visited_map.clear();
                // 由于是广搜（向下逐层搜索），所以最短路径的答案会被最先加入到res中。因此如果当前层的深度已经大于了min_level，说明之后的全部路
                // 径都会大于min_level，没有必要继续向下层搜索，直接break退出循环。
                if (path.size()>min_level){
                    break;
                }else{
                    level = path.size();
                }
            }
            string last_word = path.back();
            for (int i = 0; i < last_word.size(); ++i) {
                string new_word = last_word;
                for (int j = 'a'; j <= 'z'; ++j) {
                    new_word[i] = j;
                    // 如在词库中才能添加到路径中
                    if (word_set.find(new_word) != word_set.end()){
                        vector<string> new_path = path;
                        new_path.push_back(new_word);
                        visited_map.insert(new_word);
                        if (new_word==endWord){
                            // 找到了第一个答案，同时该答案也是最小路径，将本层的层数赋值给min_level
                            min_level = level;
                            // 加入答案集
                            res.push_back(new_path);
                        }else{
                            paths.push(new_path);
                        }
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};

    Solution sol;
    vector<vector<string>> res = sol.findLadders(beginWord, endWord, wordList);

    for(const auto& elem_lines:res){
        for(const auto& elem:elem_lines){
            cout<<elem<<"\t";
        }
        cout<<endl;
    }

    return 0;
}
