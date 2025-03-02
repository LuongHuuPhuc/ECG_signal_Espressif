# ECG Signal Measure
#### 2025/03/03 
#### Lương Hữu Phúc
*** 
## **Giới thiệu sơ lược**
- Dự án nhỏ sử dụng cảm biến AD8232 để đo tín hiệu điện tâm đồ (ECG) thông qua bộ ADC 12-bit của MCU Esp32
- Dự án này sẽ tiếp tục được phát triển và tối ưu hơn về code + hiển thị kết quả ra màn hình OLED + sử dụng wifi để gửi thông tin lên Sever
## **Chi tiết phần cứng - phần mềm sử dụng**
# 1. Hardware
* ## **01 Esp32 - 38 pins, 4MB flash memory, 520KB SRAM, sử dụng nguồn cấp bằng cáp micro-USB** <br>
![image](https://github.com/user-attachments/assets/07d970ef-ad88-44d2-b055-c6992b4bbfbc)
* ## **01 Module cảm biến ECG AD8232** <br> 
![image](https://github.com/user-attachments/assets/7e074dd4-e20f-422f-9068-c062b013bce5)
### Thông số và pinouts của AD8232 <br>

|         Pinouts          |                 Chức năng                |
---------------------------|-------------------------------------------
|       RA(Right Arm)      |          Kết nối điện cực tay phải       |
|       LA(Left Arm)       |          Kết nối điện cực tay trái       |
|       RL(Right Leg)      |         Kết nối điện cực chân phải       |
|         Output           |     Tín hiệu ECG đã được khuếch đại      |
|                          |                                          |
|         LO+/LO-          |      Phát hiện mất kết nối điện cực      |
|                          |           (HIGH = mất tín hiệu)          |
|                          |                                          |
|                          |       (Chế độ tiết kiệm năng lượng)      |
|      SDN (Shutdown)      |         Điều khiển tắt mở cảm biến       |
|                          |          HIGH = bật, LOW = tắt           |
* ## **01 Dây kết nối điểm cực** <br>
![image](https://github.com/user-attachments/assets/8e1e8e0a-d897-49c6-962c-8e426ac3abfb)
* ## **01 Mạch nguồn ổn áp AMS117 (7v-12V input, 3.3V-5V output) <br>
![image](https://github.com/user-attachments/assets/4f27250f-4f5f-4308-a1d1-60224184b1d5)
> Nên cấp nguồn ngoài cho cảm biến vì cảm biến nhiễu với môi trường, nguồn điện trực tiếp từ MCU và laptop, gây méo dạng dữ liệu !
* ## 01 Cáp nguồn USB to USB có hỗ trợ chống nhiễu Ferrite Bead <br>
 ![image](https://github.com/user-attachments/assets/68fe1ff4-7e74-4732-9820-9a13913619eb)
* ## **Dây Jumper male-male (đực - đực)**
![image](https://github.com/user-attachments/assets/ba09ff8a-18e9-4bbb-83cc-cea74f1418c5)
## Sơ dồ kết nối mạch 
# 2. Software/Firmware
