# คำถามท้ายบท 01


## 1.ไฟล์ใดบ้างที่จำเป็นสำหรับโปรเจกต์ ESP-IDF ขั้นต่ำ?

1.main/main.c	โค้ดหลักของโปรแกรม (เริ่มต้นที่ app_main())

2.CMakeLists.txt	บอกให้ระบบ build รู้ว่ามี source อะไรบ้าง และชื่อโปรเจกต์คืออะไร

3.sdkconfig	เก็บค่าการตั้งค่าระบบ (เช่น target board, Wi-Fi, log level ฯลฯ)

## 2.ความแตกต่างระหว่าง hello_esp32.bin และ hello_esp32.elf คืออะไร?

hello_esp32.elf	เป็น Executable and Linkable Format รวมโค้ด, symbol, debug info	ใช้ตอน debug (ดู symbol, stack trace)
hello_esp32.bin	เป็น Binary image ที่ถูกแปลงให้อยู่ในรูปพร้อมแฟลชลงบอร์ด	ใช้ตอน แฟลชลง ESP32

## 3.คำสั่ง idf.py set-target ทำอะไร?

กำหนดชิปที่เราจะ build ให้เหมาะกับ target board เช่น idf.py set-target esp32 จะตั้งค่า sdkconfig ให้ใช้พารามิเตอร์ของ ESP32 รุ่นปกติ

## 4.โฟลเดอร์ build/ มีไฟล์อะไรบ้าง?

hello_esp32.bin	ไฟล์ Binary สำหรับแฟลชลงบอร์ด ,hello_esp32.elf	ไฟล์ Executable สำหรับ debug
bootloader/	โฟลเดอร์ย่อยเก็บไฟล์ bootloader ,partition_table/	เก็บตาราง partition ของ Flash
compile_commands.json	ใช้โดย VSCode หรือ IDE เพื่อช่วยแนะนำโค้ด ,.map	แสดงตำแหน่งหน่วยความจำของโค้ดและข้อมูลทั้งหมด

## 5.การใช้ vTaskDelay() แทน delay() มีความสำคัญอย่างไร?

delay() (หรือ for loop delay แบบ Arduino) จะ หยุด CPU ทั้งหมด

vTaskDelay() จะ พักเฉพาะ task ปัจจุบัน แล้วให้ CPU ไปทำงาน task อื่นได้
