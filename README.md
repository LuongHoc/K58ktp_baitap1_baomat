# Lương Văn Học - K225480106025
# K58KTP - An toàn và bảo mật thông tin
# NỘI DUNG BÀI TẬP 1:
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

# -----BÀI LÀM-----
## I. Mã hoá Caesar

1. **Tên gọi:** Caesar Cipher (mã hóa dịch chuyển) – do Julius Caesar sử dụng để gửi thư bí mật.
2. **Thuật toán:**
- Mã hoá: mỗi chữ cái trong bản rõ được dịch chuyển một số vị trí k trên vòng chữ cái (mod 26).
E_k(P) = (P + k) mod 26

- Giải mã: dịch ngược lại:
D_k(C) = (C - k) mod 26
3. **Không gian khóa**

25 khóa có thể (k = 1 đến 25; k=0 là văn bản gốc, không mã hóa).

4. **Cách phá mã**

- Brute force (vét cạn): Thử tất cả 25 khóa và kiểm tra kết quả bằng mắt (dễ nhận ra văn bản có nghĩa).

- Phân tích tần suất (frequency analysis): Trong tiếng Anh, chữ 'E' (vị trí 4) xuất hiện nhiều nhất.

5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

## II.Mã Hóa Affine
**1. Tên gọi:** Affine cipher.

**2. Thuật toán:**
- Mã hoá: Xây dựng phép biến đổi tuyến tính trên vòng Z_26: E_{a,b}(x) = (a*x + b) mod 26, với x là chỉ số chữ A=0..Z=25.

a và 26 phải là nguyên tố cùng nhau (gcd(a,26)=1) để tồn tại nghịch đảo a^{-1}.

- Giải mã: D_{a,b}(y) = a^{-1} * (y - b) mod 26, trong đó a^{-1} là nghịch đảo của a mod 26.

**3. Không gian khóa**

- Số giá trị a hợp lệ = φ(26) = 12 (các a = 1,3,5,7,9,11,15,17,19,21,23,25).

- Số giá trị b = 26.

- Tổng khoá = 12 * 26 = 312 khả năng.
   
**4. Cách phá mã**

- Brute force thử 312 khả năng.

- Phân tích tần suất có thể tách thành suy luận a và b từ hai cặp chữ cái tần suất đứng đầu (nhưng thực tế phức tạp hơn Caesar).

5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

## III. Mã hoá hoán vị 

**1. Tên gọi:** Columnar transposition (mã hoán vị cột)

**2. Thuật toán:**
- Mã hoá: Chọn một khoá là một hoán vị (hoặc một từ). Ghi bản rõ theo hàng vào một lưới có số cột = độ dài khoá. Sau đó đọc các cột theo thứ tự được chỉ bởi hoán vị khoá (ví dụ theo thứ tự chữ cái của khóa).

- Giải mã: dựng lại lưới theo chiều ngược (biết số kí tự và thứ tự cột), rồi đọc theo hàng.

**3. Không gian khóa**

Nếu hoán vị chiều n, không gian = n! (ví dụ n=6 → 720). Khoá thực nghiệm thường là từ (mật mã hoá bằng từ), nên số khả năng = số hoán vị từ đó (n!).

**4. Cách phá mã**
- Nếu n nhỏ: brute-force trên n! (thử thứ tự cột).

- Kết hợp heuristics: kiểm tra sự xuất hiện của từ / cặp chữ phổ biến sau khi giải mã.

- Nếu biết plaintext ngắn gọn hoặc có mẫu, dùng ké-truy/gắn ghép.

- Kết hợp với phân tích digram/trigram để chấm điểm kết quả.

5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

## IV.Phương pháp Vigenère Cipher
**1. Tên gọi:** Vigenère cipher

**2. Thuật toán:**

- Khoá: chuỗi chữ cái K độ dài m.

- Mã hoá: với plaintext P, ký tự P_i và khoá ký tự K_{i mod m}, C_i = (P_i + K_j) mod 26 (với A=0).

- Giải mã: P_i = (C_i - K_j mod 26).

- Tương đương là các Caesar lặp lại.

**3. Không gian khoá:**

- Nếu khoá độ dài m, không gian = 26^m. (Nếu không biết m, không gian lớn).

- Nếu giới hạn m nhỏ (ví dụ m<=6), có thể brute-force trên tất cả 26^m.

**4. Cách phá mã:**

- Kasiski examination: tìm khoảng cách giữa các lặp xuất hiện của cùng một n-gram trong ciphertext để suy ra độ dài khoá m.

- Friedman test (index of coincidence) để ước lượng m.

- Sau khi biết m, chia ciphertext thành m chuỗi con (mỗi chuỗi là mọi ký tự cách nhau m), rồi áp dụng phân tích tần suất (giả sử mỗi chuỗi giống Caesar) để tìm shift của từng chuỗi.

- Nếu m chưa biết nhỏ, thử mọi m và chấm điểm bằng mẫu ngôn ngữ (chi-square).

5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

## V.Phương pháp Playfair

**1. Tên gọi:** Playfair cipher

**2. Thuật toán:**

- Dùng bảng 5×5 (loại bỏ hoặc gộp J vào I) được tạo từ khóa: viết khóa (không lặp) rồi điền các chữ cái còn lại theo thứ tự.

- Tiền xử lý plaintext:

Loại ký tự không phải chữ, viết hoa, thay J bằng I.

Tách thành digraph (cặp). Nếu một cặp là hai chữ cái giống nhau, chèn X (hoặc Q) giữa để tách.

Nếu cuối cùng lẻ, thêm X.

- Mã hoá với một cặp (A,B):

Nếu cùng hàng: thay bằng chữ bên phải (vòng sang trái nếu cuối).

Nếu cùng cột: thay bằng chữ phía dưới (vòng lên đầu nếu cuối).

Nếu khác hàng và cột: thay bằng hai chữ ở cùng hàng nhưng cột hoán đổi (hình chữ nhật).

- Giải mã: ngược lại (trái / trên thay cho phải / dưới).

**3. Không gian khóa:**

- Lý thuyết: mọi cách sắp xếp 25 ký tự → 25! ≈ 1.551e25 (≈ 10^25.19). Đây là không gian rất lớn. (Thực tế có tính tương đương do hoán vị và I/J gộp nhưng vẫn cực lớn.)

**4. Cách phá mã:**

- Brute-force toàn bộ 25! không khả thi.

- Thực nghiệm dùng heuristics: simulated annealing hoặc hill-climbing với scoring bằng ngôn ngữ (n-gram) — các thuật toán này được dùng để phá Playfair.

- Nếu có plaintext mẫu, có thể khai thác.
5. Cài đặt thuật toán mã hoá và giải mã bằng code C++

