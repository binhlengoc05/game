#  GAME NAME : AGING HEIGHTS
Đây là một dự án game 2D được phát triển bằng C++ với thư viện SDL2. Dự án được thiết kế để chạy trên Windows với trình biên dịch MinGW.
ý tưởng trò chơi dựa trên https://www.silvergames.com/en/everything-start-to-fall/gameframe#adtest

TRÌNH BIÊN DỊCH : MinGW

# THƯ VIỆN :
```bass
SDL2
SDL2_image
SDL2_mixer
```
CÔNG CỤ PHÁT TRIỂN : CodeBlocks
# HƯỚNG DẪN CÀI ĐẶT TRÒ CHƠI :
bước 1 : Mở terminal ( hoặc Git Bash trong Windows)
Bước 2 : truy cập thư mục repo:
```bass
cd đường dẫn đến thư mục muốn lưu repo
```
Bước 3: dùng lệnh sau để copy
```bass
git clone link_github_dự_án

```
ở đây :git clone https://github.com/binhlengoc05/game.git
# HƯỚNG DẪN CHƠI :
  - di chuyển trái phải bằng A( hoặc mũi tên trái) và D( hoặc mũi tên phải)
  - nhảy lên bằng Space
  - 1 số block có thể nhảy xuyên qua và đứng trên nó
  - khung hình sẽ di chuyển lên và tại 1 số điểm sẽ thay đổi trạng thái nhân vật( em bé -> cậu bé -> trưởng thành -> ông già), các chức năng di chuyển cũng thay đổi theo trạng thái nhân vật
  ![Hướng dẫn](https://raw.githubusercontent.com/binhlengoc05/game/main/huongdan.png)

# HƯỚNG PHÁT TRIỂN :
```bass
  - tạo animation, mở rộng map
  - thêm các khu vực nước, leo thang , hành động bơi
```
# NGUỒN:
- code học hỏi từ [tài liệu](https://sites.google.com/site/ltncvnu/l%E1%BB%8Bch-h%E1%BB%8Dct%C3%A0i-li%E1%BB%87u) về graphics,music,..
- học về map từ các video trên youtube
- có học hỏi AI về phần tương tác nhân vật với các khối
- ảnh nhân vật và hình nền kiểm trên mạng và tạo bằng canva.com , nhạc nền [https://opengameart.org/content/menu-music](https://opengameart.org/content/menu-music)
