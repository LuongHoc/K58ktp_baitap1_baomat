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

### Kiểm thử
**Dùng C++**
- Mã hoá

<img width="640" height="467" alt="image" src="https://github.com/user-attachments/assets/287da6fe-b928-4895-bda7-ea3b4d577c1a" />

- Giải mã

<img width="609" height="448" alt="image" src="https://github.com/user-attachments/assets/c8faa0a7-cd76-42c5-9c18-c6e10834d1c5" />

**Dùng html+css+javascript**
- Mã hoá
<img width="1878" height="1036" alt="image" src="https://github.com/user-attachments/assets/fbb67ccc-da61-4317-8c29-ea4e265fd43e" />

- Giải mã

<img width="1880" height="976" alt="image" src="https://github.com/user-attachments/assets/9725ce59-e67a-4a80-971e-242d269c61b7" />

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

### Kiểm thử
**Dùng C++**
- Mã hoá

<img width="710" height="492" alt="image" src="https://github.com/user-attachments/assets/38641766-fdda-4ada-b5de-dec8553123d5" />

- Giải mã

<img width="1113" height="645" alt="image" src="https://github.com/user-attachments/assets/da1967fd-15b7-4ac0-84e4-69bc0e3bdbb3" />

**Dùng html+css+javascript**
- Mã hoá

<img width="1690" height="981" alt="image" src="https://github.com/user-attachments/assets/fdb3fbb6-895f-42a5-a07d-25b4fa96c798" />

- Giải mã

<img width="1905" height="971" alt="image" src="https://github.com/user-attachments/assets/08cb50fd-6f63-469b-8271-9fde39df5824" />

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

### Kiểm thử
**Dùng C++**
- Mã hoá

<img width="1097" height="644" alt="image" src="https://github.com/user-attachments/assets/651c0d63-7207-49d7-b5aa-b46be1934f73" />

- Giải mã

<img width="1105" height="639" alt="image" src="https://github.com/user-attachments/assets/40c6c952-8525-4c18-a0f8-19bcded0ffc3" />

**Dùng html+css+javascript**
- Mã hoá

<img width="1820" height="965" alt="image" src="https://github.com/user-attachments/assets/0cd61023-5b91-4992-b7e0-69162b1d650c" />

- Giải mã

<img width="1824" height="962" alt="image" src="https://github.com/user-attachments/assets/28421a43-c902-40bd-b8c1-1609a292b965" />

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

### Kiểm thử
**Dùng C++**
- Mã hoá

<img width="1104" height="639" alt="image" src="https://github.com/user-attachments/assets/3093fddc-d84c-478a-b654-a1c170a6658d" />

- Giải mã

<img width="1087" height="645" alt="image" src="https://github.com/user-attachments/assets/7d7aa615-f77f-4262-9a30-8c21d86e8535" />

**Dùng html+css+javascript**
- Mã hoá

<img width="1840" height="972" alt="image" src="https://github.com/user-attachments/assets/5a400ee7-43fa-4f9a-8563-9e0c7832d2e7" />

- Giải mã

<img width="1842" height="955" alt="image" src="https://github.com/user-attachments/assets/c7565e25-c285-4946-b696-cc45a5e5abf9" />

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
### Kiểm thử
**Dùng C++**
- Mã hoá

<img width="1097" height="642" alt="image" src="https://github.com/user-attachments/assets/bfef1f02-0f48-4531-b535-28f28a728df6" />

- Giải mã

<img width="1108" height="644" alt="image" src="https://github.com/user-attachments/assets/70e8bc69-ea9d-412d-8ef4-30900026d6a3" />


**Dùng html+css+javascript**
- Mã hoá

<img width="1844" height="951" alt="image" src="https://github.com/user-attachments/assets/aae701d9-810d-49e3-913b-536debd301da" />

- Giải mã

<img width="1891" height="962" alt="image" src="https://github.com/user-attachments/assets/a3264c0f-377d-4d07-b3a8-eb05509e2b8b" />

