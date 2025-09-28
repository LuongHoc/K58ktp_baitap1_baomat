#include <iostream>
#include <string>
#include <cstdlib>   // strtol
using namespace std;

// --------- Helpers ----------
int mod(int x, int m){ int r = x % m; return (r < 0) ? r + m : r; }

int gcd_int(int a, int b){
    if (a < 0) a = -a; if (b < 0) b = -b;
    while (b){ int t = a % b; a = b; b = t; }
    return a;
}

// a^{-1} mod m (t?n t?i khi gcd(a,m)=1). N?u không có, tr? -1
int modInverse(int a, int m){
    a = mod(a, m);
    for (int x = 1; x < m; ++x)
        if (mod(a * x, m) == 0 + 1 % m) // a*x = 1 (mod m)
            return x;
    return -1;
}

// Ð?c s? nguyên t? 1 dòng (tuong thích Dev-C++)
int read_int_line(const string& prompt){
    while (1){
        cout << prompt;
        string line; if (!getline(cin, line)) return 0;
        // c-style parse
        const char* s = line.c_str();
        char* endp = NULL;
        long v = strtol(s, &endp, 10);
        if (endp == s) { cout << "Gia tri khong hop le. Nhap lai (so nguyen).\n"; continue; }
        return (int)v;
    }
}

// --------- Affine Cipher ----------
// E(p) = (a*p + b) mod 26
string affine_encrypt(const string& pt, int a, int b){
    string ct = pt;
    a = mod(a,26); b = mod(b,26);
    for (size_t i=0;i<pt.size();++i){
        unsigned char ch = pt[i];
        if ('A'<=ch && ch<='Z'){
            int p = ch - 'A';
            int c = mod(a*p + b, 26);
            ct[i] = char('A' + c);
        }else if ('a'<=ch && ch<='z'){
            int p = ch - 'a';
            int c = mod(a*p + b, 26);
            ct[i] = char('a' + c);
        }else{
            ct[i] = pt[i];
        }
    }
    return ct;
}

// D(c) = a^{-1} * (c - b) mod 26
string affine_decrypt(const string& ct, int a, int b){
    string pt = ct;
    a = mod(a,26); b = mod(b,26);
    int inv = modInverse(a, 26);
    if (inv == -1) return string("[LOI] a khong co nghich dao modulo 26 (gcd(a,26) != 1)");
    for (size_t i=0;i<ct.size();++i){
        unsigned char ch = ct[i];
        if ('A'<=ch && ch<='Z'){
            int c = ch - 'A';
            int p = mod(inv * (c - b), 26);
            pt[i] = char('A' + p);
        }else if ('a'<=ch && ch<='z'){
            int c = ch - 'a';
            int p = mod(inv * (c - b), 26);
            pt[i] = char('a' + p);
        }else{
            pt[i] = ct[i];
        }
    }
    return pt;
}

// --------- UI ----------
void print_header(){
    cout << "========================================\n";
    cout << "             THUAT TOAN AFFINE          \n";
    cout << "========================================\n\n";
}

void encrypt_flow(){
    cout << "--- MA HOA (Affine) ---\n";
    cout << "Nhap ban ro: ";
    string pt; getline(cin, pt);
    int a = read_int_line("Nhap a (gcd(a,26)=1): ");
    int b = read_int_line("Nhap b: ");
    if (gcd_int(a,26)!=1){
        cout << "[LOI] a phai nguyen to cung nhau voi 26 (vd: 1,3,5,7,9,11,15,17,19,21,23,25).\n";
        return;
    }
    string ct = affine_encrypt(pt, a, b);
    cout << "Ban ma: " << ct << "\n";
}

void decrypt_flow(){
    cout << "--- GIAI MA (Affine) ---\n";
    cout << "Nhap ban ma: ";
    string ct; getline(cin, ct);
    int a = read_int_line("Nhap a (gcd(a,26)=1): ");
    int b = read_int_line("Nhap b: ");
    if (gcd_int(a,26)!=1){
        cout << "[LOI] a phai nguyen to cung nhau voi 26.\n";
        return;
    }
    string pt = affine_decrypt(ct, a, b);
    cout << "Giai ma: " << pt << "\n";
}

int main(){
    while (1){
        system("cls"); // Windows: xoa man hinh. Tren Linux/macOS co the thay "clear"
        print_header();
        cout << "Chon chuc nang:\n";
        cout << " 1) Ma hoa (Encrypt)\n";
        cout << " 2) Giai ma (Decrypt)\n";
        cout << " 0) Thoat\n\n";
        int ch = read_int_line("Lua chon: ");
        cout << "\n";
        if (ch==1){ encrypt_flow(); }
        else if (ch==2){ decrypt_flow(); }
        else if (ch==0){ cout << "Ket thuc.\n"; break; }
        else { cout << "Chon 1 hoac 2 (0 de thoat).\n"; }

        cout << "\nNhan Enter de tiep tuc...";
        string tmp; getline(cin, tmp);
    }
    return 0;
}

