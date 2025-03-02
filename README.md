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
* Thông số
   - Nguồn cấp tối ưu: 3.3V
   - Dòng điện tiêu thụ: 170uA (thấp, tiết kiệm năng lượng)
   - Điện áp đầu ra: 0.9V - 1.5V, trung bình khoảng 1.2V
   - Dải tần hoạt động: 0.5Hz - 40Hz
   - Tích hợp Low Pass Filter (~0.5Hz): Loại bỏ trôi nền
   - Tích hợp High Pass Filter (~40Hz): Loại bỏ nhiễu tần số cao
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
* ## **01 Dây kết nối điểm cực - đầu ra Jack 3.5m** <br>
![image](https://github.com/user-attachments/assets/8e1e8e0a-d897-49c6-962c-8e426ac3abfb)
* ## **01 Mạch nguồn ổn áp AMS117 (7v-12V input, 3.3V-5V output) <br>
![image](https://github.com/user-attachments/assets/4f27250f-4f5f-4308-a1d1-60224184b1d5)
> Nên cấp nguồn ngoài cho cảm biến vì cảm biến nhiễu với môi trường, nguồn điện trực tiếp từ MCU và laptop, gây méo dạng dữ liệu !
* ## 01 Cáp nguồn USB to USB có hỗ trợ chống nhiễu Ferrite Bead <br>
 ![image](https://github.com/user-attachments/assets/68fe1ff4-7e74-4732-9820-9a13913619eb)
* ## **Dây Jumper male-male (đực - đực)**
![image](https://github.com/user-attachments/assets/ba09ff8a-18e9-4bbb-83cc-cea74f1418c5)
## Sơ dồ kết nối mạch (Components Diagram)
![image](https://github.com/user-attachments/assets/548c5a26-caeb-46bb-8cf6-d17bcdca2573)

|          AD8232          |           Esp32 MCU           | Mạch ổn áp ASM117  |
---------------------------|-------------------------------|---------------------
|       RA(Right Arm)      | (Nếu dùng jack thì không cần) |          x         | 
|       LA(Left Arm)       | (Nếu dùng jack thì không cần) |          x         |
|       RL(Right Leg)      | (Nếu dùng jack thì không cần) |          x         |
|         Output           |         GPIO34 (ADC1_6)       |          x         |
|          LO+             |            GPIO23             |          x         |
|          LO-             |            GPIO35             |          x         |
|      SDN (Shutdown)      |  GND hoặc bỏ không (optional) |          x         |
|          3.3V            |         Không kết nối         |         3.3V       |
|          GND             |         Không kết nối         |         GND        |

- Cấp nguồn từ laptop Msi GF63 Thin 11UC cho mạch ổn áp và MCU 
# 2. Software/Firmware
