# คำถาม lab1-binary-semaphores

## 1.เมื่อ give semaphore หลายครั้งติดต่อกัน จะเกิดอะไรขึ้น?
ถ้าเป็น Binary Semaphore  ค่าไม่เพิ่มเกิน 1 (ให้ซ้ำก็ไม่เปลี่ยน)
แต่ถ้าเป็น Counting Semaphore ค่าจะเพิ่มขึ้นตามจำนวนครั้งที่ give
## 2.ISR สามารถใช้ xSemaphoreGive หรือต้องใช้ xSemaphoreGiveFromISR?
xSemaphoreGiveFromISR() เพราะออกแบบให้ปลอดภัยสำหรับการเรียกใช้ใน Interrupt context
## 3.Binary Semaphore แตกต่างจาก Queue อย่างไร?
Semaphore = สัญญาณ, Queue = ข้อมูล

# คำถาม Lab2-mutex-critical-sections
## 1.เมื่อไม่ใช้ Mutex จะเกิด data corruption หรือไม่?
ไม่ใช้ Mutex: เสี่ยงข้อมูลเสีย เพราะหลาย Task เขียนพร้อมกัน
## 2.Priority Inheritance ทำงานอย่างไร?
Priority Inheritance: ยก priority ของ Task ที่ถือ Mutex ให้สูงขึ้นชั่วคราว ป้องกันแย่งคิว
## 3.Task priority มีผลต่อการเข้าถึง shared resource อย่างไร?
Task Priority: Priority สูงได้ CPU ก่อน แต่ยังต้องรอ Mutex เพื่อเข้าถึงทรัพยากรร่วม


# คำถาม Lab3-counting-semaphores

## 1.เมื่อ Producers มากกว่า Resources จะเกิดอะไรขึ้น?
Producers มากกว่า Resources: บางงานต้องรอหรือถูกปฏิเสธ เพราะทรัพยากรไม่พอ  คิวเริ่มเต็ม
## 2.Load Generator มีผลต่อ Success Rate อย่างไร?
Load Generator: ถ้าเพิ่มโหลดมากเกินไป → Success Rate ลดลง เพราะระบบประมวลผลไม่ทัน
## 3.Counting Semaphore จัดการ Resource Pool อย่างไร?
Counting Semaphore: ใช้นับจำนวนทรัพยากรที่เหลือใน Pool ปล่อย (give) เมื่อต้องการเพิ่ม และลด (take) เมื่อมีการใช้ เพื่อควบคุมไม่ให้ใช้เกินจำนวนที่มี

