#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>   // strtol
#include <cctype>    // isspace

using namespace std;

// Ð?c s? nguyên t? m?t dòng (tuong thích Dev-C++)
int read_int_line(const string &prompt) {
    while (1) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) return 0;
        size_t i = 0;
        while (i < line.size() && isspace((unsigned char)line[i])) ++i;
        if (i == line.size()) { cout << "Vui long nhap mot so.\n"; continue; }
        const char* cstr = line.c_str() + (int)i;
        char* endptr = NULL;
        long val = strtol(cstr, &endptr, 10);
        if (endptr == cstr) { cout << "Gia tri khong hop le. Vui long nhap lai (so nguyen).\n"; continue; }
        return (int)val;
    }
}

// So sánh c?p <char,index> theo ký t? (dùng cho sort ki?u cu)
bool pair_char_less(const pair<char,int>& a, const pair<char,int>& b) {
    return a.first < b.first;
}

// T?o th? t? (rank) c?a c?t d?a trên key: order[i] = rank c?a c?t i
vector<int> key_order(const string &key) {
    int k = (int)key.size();
    vector< pair<char,int> > arr;
    arr.reserve(k);
    for (int i = 0; i < k; ++i) arr.push_back(make_pair(key[i], i));

    // Cách 1 (không c?n C++11): dùng comparator hàm
    stable_sort(arr.begin(), arr.end(), pair_char_less);

    // (Ho?c có th? dùng: stable_sort(arr.begin(), arr.end());  // so sánh m?c d?nh pair)

    vector<int> order(k);
    for (int rank = 0; rank < k; ++rank) {
        order[arr[rank].second] = rank;
    }
    return order;
}

// Mã hóa: di?n theo hàng, d?c theo th? t? c?t theo rank c?a key. Pad 'X'
string columnar_encrypt(const string &pt, const string &key) {
    if (key.empty()) return string("[LOI] Key rong!");
    int k = (int)key.size();
    int n = (int)pt.size();
    int rows = (n + k - 1) / k; // ceil(n/k)

    vector< vector<char> > grid(rows, vector<char>(k, '\0'));
    int idx = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < k; ++c)
            grid[r][c] = (idx < n) ? pt[idx++] : 'X'; // pad

    vector<int> order = key_order(key);
    vector<int> colOfRank(k);
    for (int c = 0; c < k; ++c) colOfRank[order[c]] = c;

    string ct; ct.reserve(rows * k);
    for (int rank = 0; rank < k; ++rank) {
        int c = colOfRank[rank];
        for (int r = 0; r < rows; ++r) ct.push_back(grid[r][c]);
    }
    return ct;
}

// Gi?i mã
string columnar_decrypt(const string &ct, const string &key) {
    if (key.empty()) return string("[LOI] Key rong!");
    int k = (int)key.size();
    int n = (int)ct.size();
    int rows = (n + k - 1) / k;        // ceil(n/k)
    int full_cols = n % k;             // s? c?t có 'rows' ph?n t? n?u không pad
    if (full_cols == 0) full_cols = k; // n?u chia h?t, m?i c?t d?u 'rows'

    vector<int> colLen(k, rows);
    if (n < rows * k) {
        for (int c = full_cols; c < k; ++c) colLen[c] = rows - 1;
    }

    vector<int> order = key_order(key);
    vector<int> colOfRank(k);
    for (int c = 0; c < k; ++c) colOfRank[order[c]] = c;

    vector<string> cols(k);
    int idx = 0;
    for (int rank = 0; rank < k; ++rank) {
        int c = colOfRank[rank];
        int len = colLen[c];
        if (idx + len > n) len = n - idx;
        cols[c] = ct.substr(idx, len);
        idx += len;
    }

    string pt; pt.reserve(n);
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < k; ++c)
            if (r < (int)cols[c].size()) pt.push_back(cols[c][r]);

    return pt;
}

// Giao di?n don gi?n
void print_header() {
    cout << "========================================\n";
    cout << "         HOAN VI COT (Columnar)         \n";
    cout << "========================================\n\n";
}
void pause_enter() { cout << "\nNhan Enter de tro ve menu..."; string s; getline(cin, s); }

int main() {
    while (1) {
        system("cls");
        print_header();
        cout << "Chon: 1) Ma hoa  2) Giai ma  0) Thoat\n";
        cout << "Lua chon: ";
        string line; if (!getline(cin, line)) break;
        if (line.empty()) continue;
        int choice = (int)strtol(line.c_str(), NULL, 10);

        if (choice == 0) { cout << "Ket thuc.\n"; break; }
        else if (choice == 1) {
            cout << "--- MA HOA ---\nNhap ban ro: ";
            string pt; getline(cin, pt);
            cout << "Nhap key (chuoi): ";
            string key; getline(cin, key);
            if (key.empty()) { cout << "[LOI] Key rong!\n"; pause_enter(); continue; }
            cout << "Ban ma: " << columnar_encrypt(pt, key) << "\n";
            pause_enter();
        } else if (choice == 2) {
            cout << "--- GIAI MA ---\nNhap ban ma: ";
            string ct; getline(cin, ct);
            cout << "Nhap key (chuoi): ";
            string key; getline(cin, key);
            if (key.empty()) { cout << "[LOI] Key rong!\n"; pause_enter(); continue; }
            cout << "Giai ma: " << columnar_decrypt(ct, key) << "\n";
            pause_enter();
        } else {
            cout << "Lua chon khong hop le.\n";
            pause_enter();
        }
    }
    return 0;
}

