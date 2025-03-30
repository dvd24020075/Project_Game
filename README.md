	ĐẠI HỌC QUỐC GIA HÀ NỘI	CỘNG HÒA XÃ HỘI CHỦ NGHĨA VIỆT NAM
	TRƯỜNG ĐẠI HỌC CÔNG NGHỆ	Độc lập - Tự do - Hạnh phúc
		====================
BÁO CÁO BÀI TẬP LỚP MÔN LẬP TRÌNH NÂNG CAO
Sinh viên:…………Đoàn Văn Đức	…………………….Sinh ngày: 19/01/2006…..
Ngành học: ………..Công nghệ thông tin ………	Lớp:   2425II_INT2215_3
Tên game :…Bird Adventure…….	

Lối chơi, logic của game: 
+) Lối chơi : Bạn sẽ hóa thân thành một chú chim , điều khiển nó vượt qua các chướng ngại vật là những quả bom được thả rơi ngẫu nhiên từ trên cao xuống .( Người chơi có thể điều khiển nhân vật bằng các phím W-S-A-D đồng nghĩa với việc lên-xuống-trái-phải ) . Nhiệm vụ của người chơi là giúp chú chim tránh né những quả bom, đồng thời thu thập những đồng xu xuất hiện ngẫu nhiên và vương vãi trên đường đi, mỗi đông xu thu được sẽ giúp chú chim tích lũy được 10 điểm và sẽ được cộng dần vào thanh tính điểm nằm phía trên góc bên trái của màn hình chính .Cố gắng dành được nhiều điểm số nhất có thể nhưng nếu bạn bất cẩn để chim dính vào bom thì ngay lập tức 1 vụ nổ sẽ xảy ra và kết thúc luôn trò chơi ( game over ) và bạn sẽ thấy được điểm số của mình bên trên màn hình kết thúc . Liệu bạn có thể giúp chú chim bay xa nhất có thể, thu thập thật nhiều đồng xu và tránh né những hiểm nguy luôn rình rập? Một thử thách không dành cho những kẻ yếu tim .Hãy sẵn sàng đối mặt với cuộc phiêu lưu đầy căng thẳng nhưng cũng vô cùng hấp dẫn này nhé!
+) logic của game :
-Chuyển động của nhân vật ;
•	Giới hạn màn hình: Chim không thể bay ra khỏi màn hình.
•	Va chạm: Hệ thống phát hiện va chạm giúp xác định khi nào chim tiếp xúc với bom hoặc biên giới màn hình.
-Hệ thống bom;
•	Sinh ra ngẫu nhiên: Bom rơi từ trên xuống với vận tốc không thay đổi, tạo sự bất ngờ trong gameplay.
•	Nổ khi chạm: Nếu khoảng cách giữa chim và bom đạt ngưỡng xác định  , bom sẽ phát nổ, kết thúc trò chơi.
-Hệ thống đồng xu (Coin);
•	Sinh ra theo thời gian: Đồng xu xuất hiện tại các vị trí ngẫu nhiên, đòi hỏi người chơi phải linh hoạt trong việc di chuyển để thu thập.
•	Tăng điểm số: Mỗi lần ăn được đồng xu, điểm số sẽ tăng lên.
-Hiệu ứng va chạm;
•	Hiệu ứng sau va chạm: Khi bom phát nổ, một hiệu ứng đồ họa xuất hiện, sau đó màn hình Game Over sẽ hiển thị điểm số của người chơi.
-Giao diện game over;
•	Hiển thị điểm số cuối cùng: Khi trò chơi kết thúc, số điểm đạt được sẽ xuất hiện trên màn hình.

Đồ họa, âm thanh:
+) Đồ họa :
-  Nhân vật : Chú chim được thiết kế đơn giản với chuyển động đang vỗ cánh mượt mà, phản ứng linh hoạt với môi trường.
-  Background: Ảnh một con đường trong 1 khu rừng được cuộn liên tục, cùng với ảnh lúc bắt đầu vào game và khi kết thúc game (game over).
-  Hiệu ứng: Bom rơi ngẫu nhiên, nổ chân thực; điểm số hiển thị rõ ràng, mỗi khi ăn đông xu sẽ xuất hiện text +10 với màu sắc ngẫu nhiên .Điểm số của người chơi được hiển thị rõ ràng khi kết thúc.
+) Âm thanh :
- Âm thanh nền
•	Nhạc nền vui nhộn và kịch tính, tạo cảm giác thích thú và phấn khích cho người chơi.
•	Khi trò chơi kết thúc sẽ tự phát nhạc game over
- Hiệu ứng âm thanh
•	Hiệu ứng nổ: Khi bom va chạm với chim sẽ tạo ra 1 vụ nổ kèm theo âm thanh phát nổ của trái bom.
•	Âm thanh thu thập đồng xu: Khi người chơi ăn được đồng xu, một âm thanh vui tai sẽ vang lên, tạo cảm giác kích thích.

Cấu trúc của project game:
1. Thư mục và File Chính
+) src/ (Source code – chứa mã nguồn chính)
•	main.cpp – Tệp khởi động game, xử lý vòng lặp chính và cập nhật game.
•	game.cpp / game.h – Quản lý logic tổng thể của game.
•	graphics.cpp / graphics.h – Xử lý vẽ hình ảnh, tải tài nguyên đồ họa.
+) entities/ (Các đối tượng trong game)
•	bomb.cpp / bomb.h – Điều khiển bom, va chạm và hiệu ứng nổ.
•	coin.cpp / coin.h – Xử lý đồng xu, điểm số.
•	explosion.cpp / explosion.h – Hiệu ứng nổ khi va chạm.
•	score_effect.cpp / score_effect.h – Xử lí điểm số
•	def.h – Lưu trữ các hằng(Const)
+) assets/ (Tài nguyên game – hình ảnh, âm thanh, font)
•	img/ – Chứa hình ảnh nền, nhân vật, vật phẩm.
•	music/ – Chứa nhạc nền và hiệu ứng âm thanh.
•	font/ – Chứa phông chữ hiển thị điểm số.

Các chức năng đã cài được cho game:
+) Điều khiển nhân vật  (chim bay)
•	Người chơi có thể điều khiển chú chim bằng các phím điều hướng (W-S-A-D)
•	Chim có thể di chuyển lên ,xuống, sang trái và sang phải một cách mượt mà.
+) Hệ thống bom rơi và va chạm
•	Bom sẽ rơi từ trên cao xuống với tốc độ ngẫu nhiên, tạo thử thách cho người chơi.
•	Nếu bom chạm vào chim, hiệu ứng nổ sẽ diễn ra, kết thúc trò chơi.
•	Va chạm được kích hoạt theo ngưỡng khoảng cách tâm , giúp va chạm chân thực hơn, tránh trường hợp bom đi xuyên chim.
+) Hệ thống thu thập đồng xu
•	Đồng xu xuất hiện ngẫu nhiên, nếu chim ăn được sẽ tăng điểm số.
•	Hiệu ứng và âm thanh phát ra khi thu thập giúp trò chơi sinh động hơn.
+)Hiệu ứng nổ và âm thanh
•	Khi bom phát nổ, một hiệu ứng cháy nổ xuất hiện ngay tại vị trí va chạm.
•	Hiệu ứng nổ đi kèm âm thanh sống động, tạo cảm giác chân thực và căng thẳng.
+) Hiển thị điểm số khi kết thúc game
•	Khi trò chơi kết thúc, màn hình hiển thị số điểm mà người chơi đạt được.
•	Điểm số có thể hiển thị màu trắng (hoặc màu tùy chỉnh theo sở thích).
•	Điểm số hiển thị lệch lên trên để tạo bố cục đẹp hơn trên màn hình game over.
+) Cải thiện va chạm và logic di chuyển
•	Hệ thống va chạm được tối ưu để phần mỏ của chim cũng có thể chạm bom.
•	Hiệu ứng nổ chỉ xảy ra khi bom chạm sát chim, tránh trường hợp nổ quá sớm hoặc quá trễ.
+) Đồ họa và giao diện mượt mà
•	Đồ họa pixel-art đơn giản nhưng rõ ràng, dễ nhìn.
•	Hiệu ứng chuyển động của nền, chim, bom và đồng xu được lập trình để tạo cảm giác mượt mà và liền mạch.


