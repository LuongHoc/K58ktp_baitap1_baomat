# K58ktp_baitap1_baomat
# BÀI TẬP MÔN: An toàn và bảo mật thông tin
# BÀI TẬP 1:
## TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
Caesar

Affine

Hoán vị

Vigenère

Playfair
## Với mỗi phương pháp, hãy tìm hiểu:
Tên gọi

Thuật toán mã hoá, thuật toán giải mã

Không gian khóa

Cách phá mã (mà không cần khoá)

Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript

# =====BÀI LÀM=====
## mã hoá Caesar
1. Tên gọi: Caesar Cipher (mã hóa dịch chuyển) – do Julius Caesar sử dụng để gửi thư bí mật.
2. - Mã hóa: Mỗi chữ cái trong văn bản gốc (plaintext) được thay thế bằng chữ cái cách nó một khoảng cố định 
 vị trí trong bảng chữ cái (A=0, B=1, ..., Z=25). Công thức:
 Trong đó 
 là vị trí của chữ cái gốc (A=0), 
 là khóa (1 ≤ k ≤ 25). Ký tự không phải chữ cái được giữ nguyên.

   - Giải mã: Dịch chuyển ngược lại:
 Trong đó 
 là vị trí của chữ cái đã mã hóa.

Ví dụ: Plaintext "HELLO" với k=3 → Ciphertext "KHOOR".

3. Không gian khóa
25 khóa có thể (k = 1 đến 25; k=0 là văn bản gốc, không mã hóa).

4. Cách phá mã (không cần khóa)
- Brute force (vét cạn): Thử tất cả 25 khóa và kiểm tra kết quả bằng mắt (dễ nhận ra văn bản có nghĩa).
- Phân tích tần suất (frequency analysis): Trong tiếng Anh, chữ 'E' (vị trí 4) xuất hiện nhiều nhất.
5. Cài đặt thuật toán mã hoá và giải mã bằng code C++
## Mã Hóa Affine
1. Tên gọi
Mã Affine là một biến thể nâng cao của mã Caesar, sử dụng phép biến đổi tuyến tính để thay thế chữ cái. Nó được phát triển từ mã Caesar và được sử dụng trong các hệ thống mã hóa cổ điển.

2. Thuật toán mã hóa và giải mã
- Mã hóa: Sử dụng công thức: C = (a*x + b) mod 26

 Trong đó:

a và b là khóa (với gcd(a,26)=1)

x: vị trí chữ cái trong bảng chữ cái (A=0,..Z=25)

C: chữ cái sau khi mã hóa

- Giải mã: x = a_inv * (C - b) mod 26

a_inv: nghịch đảo modulo 26 của a sao cho (a*a_inv) mod 26 = 1

Ví dụ: a=5 → a_inv=21 (vì 5*21=105 ≡ 1 mod 26)

Giải mã R (C=17): x = 21*(17-8) mod 26 = 21*9 mod 26 = 189 mod 26 = 7 → H

3. Không gian khóa
312 khóa: a có 12 giá trị (1,3,5,7,9,11,15,17,19,21,23,25; gcd(a,26)=1), b có 26 giá trị (0-25).
   
4. Cách phá mã (không cần khóa)
- Brute force: Thử tất cả 312 khóa (khả thi vì nhỏ).
- Phân tích tần suất: Ánh xạ chữ phổ biến (E→4) trong ciphertext về E để suy ra a và b. Kết hợp với known-plaintext attack nếu có một phần văn bản gốc.

5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

## Phương pháp Hoán vị (Transposition Cipher)

1. Tên gọi: Transposition Cipher (Mã hoán vị) – không thay đổi ký tự nhưng thay đổi vị trí của chúng.
2. Thuật toán mã hóa và giải mã
- Mã hóa: Chia văn bản thành các khối kích thước n (dựa trên khóa). Khóa là một hoán vị của {1,2,...,n} (ví dụ: 3,1,2 cho n=3). Đọc khối theo thứ tự khóa. Padding bằng 'X' nếu cần.

Ví dụ: Text "HELLO", khóa [3,1,2] → Khối "HEL" → Đọc vị trí 3(H),1(E),2(L) → "HEL" (giữ nguyên nếu khóa là hoán vị).

- Giải mã: Tạo hoán vị nghịch đảo của khóa, áp dụng tương tự để khôi phục vị trí gốc.

Công thức chung: Với khối B[i], ciphertext = B[key[j]-1] cho j=1 đến n.

3. Không gian khóa
n! (giai thừa của kích thước khối n). Ví dụ: n=3 → 6 khóa; n=5 → 120 khóa. Không gian lớn nhanh chóng.

4. Cách phá mã (không cần khóa)
- Phân tích mẫu (pattern analysis): Với văn bản dài, tìm độ dài khối bằng cách kiểm tra khoảng cách giữa các chữ cái lặp lại (anagram detection).

- Phân tích tần suất digram/trigram: So sánh tần suất cặp chữ cái trong ciphertext với plaintext mong đợi. Brute force khả thi nếu n nhỏ.
5. Cài đặt thuật toán mã hoá và giải mã bằng code C++
## Phương pháp Vigenère Cipher
1. Tên gọi: Vigenère Cipher – "mã hóa chữ cái theo từ khóa", là phiên bản nâng cao của Caesar.
2. Thuật toán:

- Mã hóa:

C[i] = (P[i] + K[i mod m]) mod 26


P[i] là chữ cái bản rõ, K[i] là ký tự khóa, m là độ dài khóa.

- Giải mã:

P[i] = (C[i] - K[i mod m] + 26) mod 26


3. Không gian khóa:

Phụ thuộc độ dài khóa m và 26 ký tự → 26^m khả năng.

4. Cách phá mã:

Phân tích tần số theo từng chuỗi chữ cái (Kasiski test, Friedman test).

5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

## Phương pháp Playfair Cipher

1. Tên gọi: Playfair Cipher – mã hóa theo cặp chữ cái dựa trên bảng 5x5.

2. Thuật toán:

- Mã hóa:

Chia văn bản thành các cặp chữ cái.

Tạo bảng 5x5 từ khóa (ghép I/J).

Mã hóa theo quy tắc: cùng hàng, cùng cột, hoặc hình chữ nhật.

- Giải mã:

Làm ngược lại quy tắc trên.

3. Không gian khóa:

Tùy vào khóa chữ cái → 25! khả năng (bảng 5x5).

4. Cách phá mã:

Tần số chữ cái, thử kết hợp các cặp.
5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

