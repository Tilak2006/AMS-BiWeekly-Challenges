#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

long long phi(long long n) {
    long long result = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);

    vector<pair<long long, long long>> probs(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        long long ph = phi(a[i]);
        probs[i] = {ph, a[i]};
    }

    long long total_expected_val_num = 0;
    long long total_expected_val_den = 1;

    // Iterate through all 2^N subsets (approx 10^6 for N=20)
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<long long> subset;
        long long prob_num = 1;
        long long prob_den = 1;

        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                subset.push_back(a[i]);
                prob_num = (prob_num * probs[i].first) % MOD;
                prob_den = (prob_den * probs[i].second) % MOD;
            } else {
                long long num = probs[i].second - probs[i].first;
                prob_num = (prob_num * num) % MOD;
                prob_den = (prob_den * probs[i].second) % MOD;
            }
        }

        long long current_gcd = 0;
        if (!subset.empty()) {
            current_gcd = subset[0];
            for (size_t k = 1; k < subset.size(); k++) {
                current_gcd = gcd(current_gcd, subset[k]);
            }
        }

        long long term_num = (current_gcd * prob_num) % MOD;
        long long term_den = prob_den;

        long long new_num = (total_expected_val_num * term_den) % MOD;
        long long add_part = (term_num * total_expected_val_den) % MOD;
        new_num = (new_num + add_part) % MOD;

        total_expected_val_den = (total_expected_val_den * term_den) % MOD;
        total_expected_val_num = new_num;
    }

    long long inv_den = modInverse(total_expected_val_den);
    long long answer = (total_expected_val_num * inv_den) % MOD;
    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
