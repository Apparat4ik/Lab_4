#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Метод Борда
pair<string, map<string, int>> BordaWinner(const vector<vector<string>>& votes, const vector<string>& candidates) {
    map<string, int> scores;
    int n = candidates.size();

    for (const vector<string>& vote : votes) {
        for (int i = 0; i < n; ++i) {
            scores[vote[i]] += n - i - 1;
        }
    }

    string winner;
    int maxScore = -1;
    for (pair<string, int> score : scores) {
        if (score.second > maxScore) {
            maxScore = score.second;
            winner = score.first;
        }
    }
    return {winner, scores};
}

// Метод Кондорсе
string CondorcetWinner(const vector<vector<string>>& votes, const vector<string>& candidates) {
    map<string, map<string, int>> pairwiseWins;

    for (const string& a : candidates) {
        for (const string& b : candidates) {
            if (a == b) continue;

            int a_wins = 0;
            for (const vector<string>& vote : votes) {
                int posA = find(vote.begin(), vote.end(), a) - vote.begin();
                int posB = find(vote.begin(), vote.end(), b) - vote.begin();
                if (posA < posB) {a_wins++;}
            }

            if (a_wins > votes.size() / 2){
                pairwiseWins[a][b] = 1;
            }
        }
    }

    for (const string& a : candidates) {
        bool winsAll = true;
        for (const string& b : candidates) {
            if (a == b) continue;
            if (pairwiseWins[a][b] != 1)
                winsAll = false;
        }
        if (winsAll) return a;
    }
    return "";
}

// Вывод баллов
void PrintScores(const map<string, int>& scores) {
    for (const pair<const string, int>& vote : scores) {
        cout << vote.first << ": " << vote.second << " баллов" << endl;
    }
}

int main() {
    int n, k;
    cout << "Введите количество кандидатов: ";
    cin >> n;

    cout << "Введите количество избирателей: ";
    cin >> k;

    vector<string> candidates(n);
    cout << "Введите имена кандидатов:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> candidates[i];
    }

    vector<vector<string>> votes(k);
    cout << "Введите предпочтения каждого избирателя (по " << n << " имени(м) в порядке убывания предпочтения):" << endl;
    for (vector<string>& vt : votes) {
        vt.resize(n);
        for (string& nm : vt) {
            cin >> nm;
        }
    }

    pair<string, map<string, int>> score = BordaWinner(votes, candidates);
    cout << " Метод Борда: победитель — " << score.first << endl;
    PrintScores(score.second);

    string condorcet = CondorcetWinner(votes, candidates);
    if (!condorcet.empty())
        cout << "Метод Кондорсе: победитель — " << condorcet << endl;
    else
        cout << "Метод Кондорсе: победителя нет" << endl;

    return 0;
}
