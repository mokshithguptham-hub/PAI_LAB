#include <bits/stdc++.h>
using namespace std;

int main() {
    string obs[] = {"walk", "shop", "clean"};
    int T = 3;
    int N = 2;

    double start[] = {0.6, 0.4};

    double trans[2][2] = {
        {0.7, 0.3},
        {0.4, 0.6}
    };

    double emit[2][3] = {
        {0.1, 0.4, 0.5},
        {0.6, 0.3, 0.1}
    };

    map<string, int> obsIndex;
    obsIndex["walk"] = 0;
    obsIndex["shop"] = 1;
    obsIndex["clean"] = 2;

    double alpha[3][2];

    // Initialization
    for (int i = 0; i < N; i++) {
        alpha[0][i] = start[i] * emit[i][obsIndex[obs[0]]];
    }

    // Recursion
    for (int t = 1; t < T; t++) {
        for (int j = 0; j < N; j++) {
            alpha[t][j] = 0;
            for (int i = 0; i < N; i++) {
                alpha[t][j] += alpha[t - 1][i] * trans[i][j];
            }
            alpha[t][j] *= emit[j][obsIndex[obs[t]]];
        }
    }

    // Termination
    double prob = 0;
    for (int i = 0; i < N; i++) {
        prob += alpha[T - 1][i];
    }

    cout << fixed << setprecision(6);
    cout << "Probability of observation sequence: " << prob << endl;

    return 0;
}
