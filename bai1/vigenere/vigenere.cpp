// vigenere_devcpp.cpp
#include <iostream>
#include <string>
#include <cctype>   // isalpha, isupper, islower
using namespace std;

string normalize_key(const string &raw) {
    string k;
    for (size_t i = 0; i < raw.size(); ++i) {
        unsigned char ch = raw[i];
        if (isalpha(ch)) {
            if (isupper(ch)) k.push_back(ch);
            else k.push_back(char(toupper(ch)));
        }
    }
    return k;
}

string vigenere_encrypt(const string &pt, const string &key) {
    if (key.empty()) return string("[LOI] Key rong!");
    string ct = pt;
    string K = normalize_key(key);
    if (K.empty()) return string("[LOI] Key phai chua it nhat 1 chu cai A-Z.");
    size_t ki = 0;
    for (size_t i = 0; i < pt.size(); ++i) {
        unsigned char ch = pt[i];
        if (isalpha(ch)) {
            int shift = K[ki % K.size()] - 'A'; // 0..25
            if (isupper(ch)) {
                ct[i] = char('A' + ( (ch - 'A') + shift ) % 26);
            } else {
                ct[i] = char('a' + ( (ch - 'a') + shift ) % 26);
            }
            ++ki;
        } else {
            ct[i] = ch;
        }
    }
    return ct;
}

string vigenere_decrypt(const string &ct, const string &key) {
    if (key.empty()) return string("[LOI] Key rong!");
    string pt = ct;
    string K = normalize_key(key);
    if (K.empty()) return string("[LOI] Key phai chua it nhat 1 chu cai A-Z.");
    size_t ki = 0;
    for (size_t i = 0; i < ct.size(); ++i) {
        unsigned char ch = ct[i];
        if (isalpha(ch)) {
            int shift = K[ki % K.size()] - 'A'; // 0..25
            if (isupper(ch)) {
                pt[i] = char('A' + ( (ch - 'A') - shift + 26 ) % 26);
            } else {
                pt[i] = char('a' + ( (ch - 'a') - shift + 26 ) % 26);
            }
            ++ki;
        } else {
            pt[i] = ch;
        }
    }
    return pt;
}

// helper IO
int read_int_line(const string &prompt) {
    while (1) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) return 0;
        // trim leading spaces
        size_t i = 0;
        while (i < line.size() && isspace((unsigned char)line[i])) ++i;
        if (i == line.size()) { cout << "Vui long nhap 1 so.\n"; continue; }
        // parse integer manually (simple)
        bool neg = false;
        if (line[i] == '+' || line[i] == '-') {
            if (line[i] == '-') neg = true;
            ++i;
        }
        long v = 0;
        bool ok = false;
        for (; i < line.size(); ++i) {
            char c = line[i];
            if (c < '0' || c > '9') break;
            ok = true;
            v = v * 10 + (c - '0');
        }
        if (!ok) { cout << "Gia tri khong hop le. Nhap lai.\n"; continue; }
        if (neg) v = -v;
        return (int)v;
    }
}

void pause_enter() {
    cout << "\nNhan Enter de tro ve menu...";
    string s; getline(cin, s);
}

void print_header() {
    cout << "========================================\n";
    cout << "           THUAT TOAN VIGENERE         \n";
    cout << "========================================\n\n";
}

void encrypt_flow() {
    cout << "--- MA HOA (Vigenere) ---\n";
    cout << "Nhap van ban: ";
    string pt; getline(cin, pt);
    cout << "Nhap key (chi chu cai A-Z): ";
    string key; getline(cin, key);
    string ct = vigenere_encrypt(pt, key);
    cout << "Ban ma: " << ct << "\n";
}

void decrypt_flow() {
    cout << "--- GIAI MA (Vigenere) ---\n";
    cout << "Nhap ban ma: ";
    string ct; getline(cin, ct);
    cout << "Nhap key (chi chu cai A-Z): ";
    string key; getline(cin, key);
    string pt = vigenere_decrypt(ct, key);
    cout << "Giai ma: " << pt << "\n";
}

int main() {
    while (1) {
        system("cls"); // Windows console clear
        print_header();
        cout << "Chon chuc nang:\n";
        cout << " 1) Ma hoa (Encrypt)\n";
        cout << " 2) Giai ma (Decrypt)\n";
        cout << " 0) Thoat\n\n";
        int choice = read_int_line("Lua chon cua ban: ");
        cout << "\n";
        if (choice == 1) {
            encrypt_flow();
            pause_enter();
        } else if (choice == 2) {
            decrypt_flow();
            pause_enter();
        } else if (choice == 0) {
            cout << "Ket thuc.\n";
            break;
        } else {
            cout << "Lua chon khong hop le. Vui long chon 1 hoac 2 (hoac 0 de thoat).\n";
            pause_enter();
        }
    }
    return 0;
}

