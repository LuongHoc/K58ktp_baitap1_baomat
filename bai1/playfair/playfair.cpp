#include <iostream>
#include <string>
#include <vector>
#include <cctype>   // isalpha, toupper
#include <cstdlib>  // strtol
using namespace std;

// ========== ti?n ích nh?p s? ki?u cu (tuong thích Dev-C++) ==========
int read_int_line(const string &prompt) {
    while (1) {
        cout << prompt;
        string line; if (!getline(cin, line)) return 0;
        // parse tay
        size_t i = 0; while (i < line.size() && isspace((unsigned char)line[i])) ++i;
        if (i == line.size()) { cout << "Vui long nhap so.\n"; continue; }
        bool neg = false;
        if (line[i] == '+' || line[i] == '-') { neg = (line[i] == '-'); ++i; }
        long v = 0; bool ok = false;
        for (; i < line.size() && isdigit((unsigned char)line[i]); ++i) { ok = true; v = v*10 + (line[i]-'0'); }
        if (!ok) { cout << "Gia tri khong hop le. Nhap lai.\n"; continue; }
        if (neg) v = -v;
        return (int)v;
    }
}

void pause_enter() { cout << "\nNhan Enter de tro ve menu..."; string s; getline(cin, s); }

void print_header(){
    cout << "========================================\n";
    cout << "            PLAYFAIR  CIPHER            \n";
    cout << "========================================\n";
    cout << "Quy uoc: chi A-Z, J->I, bo ky tu khac, chen X khi trung/so le.\n\n";
}

// ========== Xay dung bang 5x5 ==========
struct PFTable {
    char m[5][5];
    int row[26];
    int col[26];
};

string normalize_key(const string& raw) {
    bool seen[26]; for (int i=0;i<26;++i) seen[i]=false;
    seen['J'-'A'] = true; // loai J (gop J->I)
    string out;
    for (size_t i=0;i<raw.size();++i){
        unsigned char ch = raw[i];
        if (!isalpha(ch)) continue;
        ch = (unsigned char)toupper(ch);
        if (ch=='J') ch='I';
        int idx = ch - 'A';
        if (!seen[idx]){ seen[idx]=true; out.push_back(ch); }
    }
    // bo sung cac chu con lai
    for (char ch='A'; ch<='Z'; ++ch){
        if (ch=='J') continue;
        int idx = ch - 'A';
        if (!seen[idx]){ seen[idx]=true; out.push_back(ch); }
    }
    return out; // do dai 25
}

PFTable make_table(const string& keyRaw){
    string seq = normalize_key(keyRaw);
    PFTable t;
    // khoi tao row/col -1
    for (int i=0;i<26;++i){ t.row[i] = -1; t.col[i] = -1; }
    int k=0;
    for (int r=0;r<5;++r){
        for (int c=0;c<5;++c){
            char ch = seq[k++];
            t.m[r][c] = ch;
            t.row[ch-'A'] = r;
            t.col[ch-'A'] = c;
        }
    }
    // map J -> I
    t.row['J'-'A'] = t.row['I'-'A'];
    t.col['J'-'A'] = t.col['I'-'A'];
    return t;
}

// ========== Tien xu ly van ban thanh cac cap ==========
string sanitize_text(const string& raw) {
    string s;
    for (size_t i=0;i<raw.size();++i){
        unsigned char ch = raw[i];
        if (isalpha(ch)){
            ch = (unsigned char)toupper(ch);
            if (ch=='J') ch='I';
            s.push_back(ch);
        }
    }
    return s;
}

string make_digraphs(const string& clean){
    string out;
    for (size_t i=0;i<clean.size();){
        char a = clean[i];
        char b = 0;
        if (i+1 < clean.size()) b = clean[i+1];
        if (b==0){ // cuoi le
            out.push_back(a); out.push_back('X'); break;
        }
        if (a==b){ // trung chu trong 1 cap -> chen X vao giua
            out.push_back(a); out.push_back('X');
            ++i; // chi nhay 1
        }else{
            out.push_back(a); out.push_back(b);
            i += 2;
        }
    }
    // neu sau vong lap ma van le (truong hop chuoi rong), bo sung
    if (out.size()%2==1) out.push_back('X');
    return out;
}

// ========== Ma hoa / Giai ma ==========
string playfair_encrypt(const string& plaintext, const string& key){
    PFTable t = make_table(key);
    string s = make_digraphs(sanitize_text(plaintext));
    string out = s;
    for (size_t i=0;i<s.size(); i+=2){
        char a=s[i], b=s[i+1];
        int ar=t.row[a-'A'], ac=t.col[a-'A'];
        int br=t.row[b-'A'], bc=t.col[b-'A'];
        if (ar==br){ // cung hang: dich sang phai
            out[i]   = t.m[ar][(ac+1)%5];
            out[i+1] = t.m[br][(bc+1)%5];
        }else if (ac==bc){ // cung cot: dich xuong
            out[i]   = t.m[(ar+1)%5][ac];
            out[i+1] = t.m[(br+1)%5][bc];
        }else{ // hinh chu nhat: doi cot
            out[i]   = t.m[ar][bc];
            out[i+1] = t.m[br][ac];
        }
    }
    return out;
}

string playfair_decrypt(const string& ciphertext, const string& key){
    PFTable t = make_table(key);
    string s = sanitize_text(ciphertext); // ciphertext co the da la A-Z
    if (s.size()%2==1) s.push_back('X');  // an toan
    string out = s;
    for (size_t i=0;i<s.size(); i+=2){
        char a=s[i], b=s[i+1];
        int ar=t.row[a-'A'], ac=t.col[a-'A'];
        int br=t.row[b-'A'], bc=t.col[b-'A'];
        if (ar==br){ // cung hang: dich trai
            out[i]   = t.m[ar][(ac+4)%5];
            out[i+1] = t.m[br][(bc+4)%5];
        }else if (ac==bc){ // cung cot: dich len
            out[i]   = t.m[(ar+4)%5][ac];
            out[i+1] = t.m[(br+4)%5][bc];
        }else{ // hinh chu nhat
            out[i]   = t.m[ar][ac==bc?ac:bc]; // se ghi de ngay ben duoi
            out[i+1] = t.m[br][br==ar?bc:ac];
            out[i]   = t.m[ar][bc];
            out[i+1] = t.m[br][ac];
        }
    }
    return out;
}

// ========== UI don gian ==========
void encrypt_flow(){
    cout << "--- MA HOA (Playfair) ---\n";
    cout << "Nhap key: ";
    string key; getline(cin, key);
    cout << "Nhap van ban: ";
    string pt; getline(cin, pt);
    string ct = playfair_encrypt(pt, key);
    cout << "Ban ma: " << ct << "\n";
}
void decrypt_flow(){
    cout << "--- GIAI MA (Playfair) ---\n";
    cout << "Nhap key: ";
    string key; getline(cin, key);
    cout << "Nhap ban ma: ";
    string ct; getline(cin, ct);
    string pt = playfair_decrypt(ct, key);
    cout << "Giai ma: " << pt ;
}

int main(){
    while (1){
        system("cls"); // Windows: clear; Linux/macOS: thay "clear"
        print_header();
        cout << "Chon chuc nang:\n";
        cout << " 1) Ma hoa (Encrypt)\n";
        cout << " 2) Giai ma (Decrypt)\n";
        cout << " 0) Thoat\n\n";
        int ch = read_int_line("Lua chon: "); cout << "\n";
        if (ch==1){ encrypt_flow(); pause_enter(); }
        else if (ch==2){ decrypt_flow(); pause_enter(); }
        else if (ch==0){ cout << "Ket thuc.\n"; break; }
        else { cout << "Chon 1 hoac 2 (0 de thoat).\n"; pause_enter(); }
    }
    return 0;
}

