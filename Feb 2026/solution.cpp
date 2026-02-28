#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= 100;
    }

    int count = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int s = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
                s += a[i];
        if (s % 100 == 0)
            count++;
    }

    cout << count << endl;
    return 0;
}
