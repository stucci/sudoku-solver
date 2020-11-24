// [再帰関数を学ぶと、どんな世界が広がるか - Qiita](https://qiita.com/drken/items/23a4f604fa3f505dd5ad?utm_content=buffer0f134&utm_medium=social&utm_source=twitter.com&utm_campaign=buffer)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using Field = vector<vector<int> >; // 盤面を二次元配列で表す

// res に見つかった答えを格納する, 答えが一つとは限らないので res を vector<Filed> 型とする
void rec(Field &field, vector<Field> &res) {
    // 空きマスを探す
    int emptyi = -1, emptyj = -1;
    for (int i = 0; i < 9 && emptyi == -1; ++i) {
        for (int j = 0; j < 9 && emptyj == -1; ++j) {
            if (field[i][j] == -1) {
                emptyi = i, emptyj = j;
                break;
            }
        }
    }

    // ベースケース (すべて埋めて空きマスがない)
    if (emptyi == -1 || emptyj == -1) {
        res.push_back(field);      
        return;
    }

    // 空きマスに入れられる数字を求める
    vector<bool> canuse(10, 1); // canuse[v] := 空きマスに v を入れられるかどうか
    for (int i = 0; i < 9; ++i) {
        // 同じ列に同じ数字はダメ
        if (field[emptyi][i] != -1) canuse[field[emptyi][i]] = false;

        // 同じ行に同じ数字はダメ
        if (field[i][emptyj] != -1) canuse[field[i][emptyj]] = false;

        // 同じブロックに同じ数字はダメ
        int bi = emptyi / 3 * 3 + 1, bj = emptyj / 3 * 3 + 1; // 同じブロックの中央
        for (int di = bi-1; di <= bi+1; ++di) 
            for (int dj = bj-1; dj <= bj+1; ++dj)
                if (field[di][dj] != -1)
                    canuse[field[di][dj]] = false;
    }

    // 再帰的に探索
    for (int v = 1; v <= 9; ++v) {
        if (!canuse[v]) continue;
        field[emptyi][emptyj] = v; // 空きマスに数値 v を置く
        rec(field, res);
    }

    // 数値を置いていた空きマスを元の空きマスに戻す (この処理をバックトラックと呼ぶ)
    field[emptyi][emptyj] = -1;
}

int main() {
    // 入力
    Field field(9, vector<int>(9, -1)); // -1 は未確定
    for (int i = 0; i < 9; ++i) {
        string line; cin >> line;
        for (int j = 0; j < 9; ++j) {
            if (line[j] == '*') continue;

            // line[j] は char 型の '0' 〜 '9'　なので、これらを 0 〜 9 にする
            int num = line[j] - '0'; 
            field[i][j] = num;
        }
    }

    // 再帰的に解く
    vector<Field> res;
    rec(field, res);

    // 答えを出力する
    if (res.size() == 0) cout << "no solutions." << endl;
    else if (res.size() > 1) cout << "more than one solutions." << endl;
    else {
        Field ans = res[0];
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }
}
