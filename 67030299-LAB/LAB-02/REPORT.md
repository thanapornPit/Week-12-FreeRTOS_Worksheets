# คำถาม Lab1-task-priority

## 1.Priority ไหนทำงานมากที่สุด? เพราะอะไร?
Task ที่มี Priority สูงสุด จะได้ CPU ก่อนเสมอ เพราะ FreeRTOS ใช้ Preemptive Scheduling หมายถึงเมื่อมี Task ที่ priority สูงกว่าพร้อมรัน ระบบจะสลับให้มันทำงานทันที
## 2.เกิด Priority Inversion หรือไม่? จะแก้ไขได้อย่างไร?
เกิดได้เมื่อ Task priority ต่ำ ถือ resource แก้โดย ใช้ Priority Inheritance ระบบจะยก priority ของ task ที่ถือ mutex ชั่วคราวให้สูงขึ้นเท่ากับ task ที่รอ


## 3.Tasks ที่มี priority เดียวกันทำงานอย่างไร?
ถ้ามีหลาย Task ที่ priority เท่ากัน ระบบจะใช้ Round-Robin Scheduling
คือสลับกันรันทีละช่วงเวลา (time slice) เท่า ๆ กัน


## 4.การเปลี่ยน Priority แบบ dynamic ส่งผลอย่างไร?
สามารถทำให้ Task เปลี่ยนลำดับความสำคัญระหว่างรันได้ ถ้าเพิ่ม priority  Task อาจแย่ง CPU จาก task อื่น ถ้าลด priority → Task จะทำงานช้าลง 


## 5.CPU utilization ของแต่ละ priority เป็นอย่างไร?
Task ที่มี priority สูง จะใช้ CPU มากกว่า
Task priority ต่ำจะได้ CPU น้อยลง โดยเฉพาะถ้ามีงานระดับสูงทำงานตลอดเวลา

# คำถาม Lab2-task-states
## 1.Task อยู่ใน Running state เมื่อไหร่บ้าง?
เมื่อ Task นั้นกำลังถูก CPU รันอยู่ (มี Priority สูงสุดในขณะนั้น และไม่ถูก Block หรือ Suspend)
## 2.ความแตกต่างระหว่าง Ready และ Blocked state คืออะไร?
Ready: พร้อมรันแต่ยังไม่ได้คิว CPU
Blocked: รอเหตุการณ์ เช่น timer, delay, semaphore 
## 3.การใช้ vTaskDelay() ทำให้ task อยู่ใน state ใด?
ทำให้ Task เข้า Blocked state ชั่วคราวจนเวลาครบ
## 4.การ Suspend task ต่างจาก Block อย่างไร?
Suspend: ถูกหยุดด้วยคำสั่ง (เช่น vTaskSuspend())
Block: หยุดเพราะรอ event หรือ delay เอง
## 5.Task ที่ถูก Delete จะกลับมาได้หรือไม่?
ไม่สามารถกลับมาได้ ต้อง xTaskCreate() ใหม่เท่านั้น

# คำถาม Lab3-stack-monitoringab2-task-states
## 1.Task ไหนใช้ stack มากที่สุด? เพราะอะไร?
มักเป็น Task ที่มี การเรียกฟังก์ชันซ้อนหลายระดับ หรือใช้ ตัวแปร array ใหญ่ใน stack
## 2.การใช้ heap แทน stack มีข้อดีอย่างไร?
ประหยัด stack ของ Task เพราะข้อมูลขนาดใหญ่ถูกเก็บใน heap ที่มีพื้นที่กว้างกว่า
## 3.Stack overflow เกิดขึ้นเมื่อไหร่และทำอย่างไรป้องกัน?
เกิดเมื่อใช้ stack เกินขนาดที่กำหนด ข้อมูลทับกัน, โปรแกรม reset ป้องกันได้โดยเพิ่ม stack size 
## 4.การตั้งค่า stack size ควรพิจารณาจากอะไร?
พิจารณาจากจำนวนตัวแปรภายใน, ฟังก์ชันที่ซ้อน, และ library ที่เรียกใช้
## 5.Recursion ส่งผลต่อ stack usage อย่างไร?
การเรียกฟังก์ชันซ้ำตัวเองใช้ stack ซ้อนเพิ่มทุกครั้ง ทำให้ stack ใช้มากขึ้นและเสี่ยง overflow

