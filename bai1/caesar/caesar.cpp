// caesar_simple_devcpp.cpp
#include <iostream>
#include <string>
#include <cstdlib>   // strtol
using namespace std;

string caesar_encrypt(const string& pt, int k) {
    string ct = pt;
    k = (k % 26 + 26) % 26;
    for (size_t i = 0; i < pt.size(); ++i) {
        unsigned char ch = pt[i];
        if ('A' <= ch && ch <= 'Z') ct[i] = char('A' + (ch - 'A' + k) % 26);
        else if ('a' <= ch && ch <= 'z') ct[i] = char('a' + (ch - 'a' + k) % 26);
        else ct[i] = pt[i];
    }
    return ct;
}

string caesar_decrypt(const string& ct, int k) {
    return caesar_encrypt(ct, -k);
}

int read_int_line(const string &prompt) {
    while (1) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) return 0;
        // trim leading spaces
        size_t i = 0;
        while (i < line.size() && isspace((unsigned char)line[i])) ++i;
        if (i == line.size()) { cout << "Vui long nhap mot so nguyen.\n"; continue; }
        const char* cstr = line.c_str() + (int)i;
        char* endptr = NULL;
        long val = strtol(cstr, &endptr, 10);
        if (endptr == cstr) {
            cout << "Gia tri khong hop le. Vui long nhap lai (so nguyen).\n";
            continue;
        }
        return (int)val;
    }
}

void pause_enter() {
    cout << "\nNhan Enter de tro ve menu...";
    string s; getline(cin, s);
}

void print_header() {
    cout << "========================================\n";
    cout << "            THUAT TOAN CAESAR           \n";
    cout << "========================================\n\n";
}

void encrypt_flow() {
    cout << "--- MA HOA ---\n";
    cout << "Nhap ban ro: ";
    string pt; getline(cin, pt);
    int k = read_int_line("Nhap khoa k (so nguyen): ");
    string ct = caesar_encrypt(pt, k);
    cout << "Ban ma: " << ct << "\n";
}

void decrypt_flow() {
    cout << "--- GIAI MA ---\n";
    cout << "Nhap ban ma: ";
    string ct; getline(cin, ct);
    int k = read_int_line("Nhap khoa k (so nguyen): ");
    string pt = caesar_decrypt(ct, k);
    cout << "Giai ma: " << pt << "\n";
}

int main() {
    while (1) {
        system("cls"); // Windows: xoa man hinh
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

