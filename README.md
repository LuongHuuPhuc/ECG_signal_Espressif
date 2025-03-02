# ECG_signal_measure
#### 2025/03/03 
#### Lương Hữu Phúc
*** 
## **Giới thiệu sơ lược**
- Dự án nhỏ sử dụng cảm biến AD8232 để đo tín hiệu điện tâm đồ (ECG) thông qua bộ ADC 12-bit của MCU Esp32
- Dự án này sẽ tiếp tục được phát triển và tối ưu hơn về code + hiển thị kết quả ra màn hình OLED + sử dụng wifi để gửi thông tin lên Sever
## **Chi tiết phần cứng - phần mềm sử dụng**
1. Hardware
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
|--------------------------|------------------------------------------|
|         LO+/LO-          |      Phát hiện mất kết nối điện cực      |
|                          |           (HIGH = mất tín hiệu)          |
|--------------------------|------------------------------------------|
|                          |       (Chế độ tiết kiệm năng lượng)      |
|      SDN (Shutdown)      |         Điều khiển tắt mở cảm biến       |
|                          |          HIGH = bật, LOW = tắt           |

2. Software/Firmware
