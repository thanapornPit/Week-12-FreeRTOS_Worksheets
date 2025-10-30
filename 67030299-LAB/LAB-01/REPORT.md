
# คำถามท้ายบท LAB01-setup-first-project


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



# คำถามท้ายบท Lab02-hello-world

## 1.ความแตกต่างระหว่าง printf() และ ESP_LOGI() คืออะไร?

printf()  แสดงข้อความธรรมดา เหมือนภาษา C ทั่วไป ไม่มีระบบจัดการระดับ log

ESP_LOGI(TAG, "ข้อความ") ใช้ระบบ log ของ ESP-IDF มีระดับ (ERROR, WARN, INFO, DEBUG, VERBOSE) และมี tag ช่วยระบุแหล่งที่มา

## 2.Log level ไหนที่จะแสดงใน default configuration?

ค่า default คือ INFO แสดงเฉพาะระดับ ERROR, WARN, และ INFO

## 3.การใช้ ESP_ERROR_CHECK() มีประโยชน์อย่างไร?

ใช้ตรวจผลลัพธ์ของฟังก์ชันที่คืนค่า esp_err_t ถ้ามี error  ระบบจะแจ้ง log และ รีสตาร์ตอัตโนมัติ ทำให้โค้ดปลอดภัยและดีบักง่ายกว่า

## 4.คำสั่งใดในการออกจาก Monitor mode?

กด Ctrl + ] เพื่อออกจากโหมด monitor และกลับไป command line

## 5.การตั้งค่า Log level สำหรับ tag เฉพาะทำอย่างไร?

เช่น esp_log_level_set("wifi", ESP_LOG_ERROR); จะให้ tag "wifi" แสดงเฉพาะ log ระดับ ERROR เท่านั้น

# คำถามท้ายบท Lab03-first-task

## 1.เหตุใด Task function ต้องมี infinite loop?

เพราะถ้าไม่มีลูป Task จะจบและถูกลบไปทันทีหลังรันเสร็จ การใช้ while(1) ทำให้ Task ทำงานซ้ำ ๆ เช่น อ่าน sensor หรือกระพริบไฟ

## 2.ความหมายของ stack size ใน xTaskCreate() คืออะไร?

คือ พื้นที่หน่วยความจำที่ Task ใช้เก็บตัวแปรภายในของตัวเอง หน่วยเป็น word (4 byte) เช่น 2048 หมายถึง 8 KB stack

## 3.ความแตกต่างระหว่าง vTaskDelay() และ vTaskDelayUntil()?

vTaskDelay() → หน่วงเวลานับจากตอนนี้ (delay แบบทั่วไป)

vTaskDelayUntil() → หน่วงโดยอิงเวลารอบก่อน เพื่อให้คาบเวลาเท่ากันทุกครั้ง เหมาะกับงานแบบ real-time

## 4.การใช้ vTaskDelete(NULL) vs vTaskDelete(handle) ต่างกันอย่างไร?

vTaskDelete(NULL) → ให้ Task ปัจจุบันหยุดตัวเอง

vTaskDelete(handle) → ลบ Task อื่น โดยใช้ handle ที่ระบุไว้ตอนสร้าง

## 5.Priority 0 กับ Priority 24 อันไหนสูงกว่า?

Priority 24 สูงกว่า Priority 0 เพราะ ตัวเลขยิ่งมากความสำคัญยิ่งสูง 
