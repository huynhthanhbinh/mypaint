1653006
Huynh Thanh Binh
16CLC1
FIT - HCMUS

MyPaint - Personal Project
Course: Programming Windows

P2 ( 2018/Jul/08th )

Debug: x86 Local Windows Debugger !!!

ĐÃ HOÀN THÀNH :
+ Khi user chọn toolbar button / menu item -> draw tương ứng
+ Toolbar button added by default : 
	-> New | Open | Save | Print || Line | Ellipse | Rectangle | Select | Text || ColorDlg || FontDlg
+ Tạo cấu trúc dữ liệu, lưu trữ cho 4 object: Line, Rectangle, Ellipse, Text
	-> Em dùng lập trình hướng đối tượng, 4 đối tượng kế thừa Object và 1 vector dạng <Object*> 
+ Color, Font được lưu trữ riêng cho mỗi child window (lưu trữ trong struct CHILD_WND_DATA)
+ Object đã vẽ lưu trữ riêng cho mỗi child window (lưu trữ trong struct CHILD_WND_DATA (vector <object*>)
+ Vẽ lại các object cho Child Window (WM_PAINT)
+ Save File, lưu dưới dạng ios::binary, extension ".drw" thành công
+ Open File, đọc dưới dạng ios::binary, extension ".drw" thành công
+ On Save : File Save Title Default = "Noname-*.drw" (GetWindowText)
+ On Open : Gán thành công tên file lên title child window (SetWindowText)


CHƯA HOÀN THÀNH :
- Mode Insert Text 
- Mode Select (Edit Object)


KHÁC /LÀM THÊM :
- Set default draw mode: Line 
- Set default child window rgb color black (rgb 0,0,0)
- Toolbar draw checked by mode 
- warning trước khi close program
- Lưu trữ project trên repository của BitBucket


Link Bitbucket << in private mode at the moment >>
https://bitbucket.org/huynhthanhbinh1998/1653006_mypaint/src/master/


Tham khảo:
- Slide bài giảng môn học
- Bài giảng trên lớp học
- MSDN 


Phiên bản Visual Studio:
- VS2017 Community v15.7.4