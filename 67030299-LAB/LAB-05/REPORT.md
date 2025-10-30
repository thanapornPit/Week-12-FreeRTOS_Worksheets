# คำถาม
## 1.Watchdog Design: เหตุใดต้องใช้ separate timer สำหรับ feeding watchdog?
เพื่อให้ watchdog ถูก feed อย่างสม่ำเสมอจาก timer ที่ “เชื่อถือได้” — ถ้า task หลักค้าง watchdog จะจับได้จริง ไม่ถูกหลอกด้วย feed ที่มาจาก task เดิม
## 2.Pattern Timing: อธิบายการเลือก Timer Period สำหรับแต่ละ pattern
เลือกตามลักษณะงาน  งานเร็วใช้ period สั้น, งานตรวจสถานะทั่วไปใช้ period ยาว เพื่อให้สมดุลระหว่างความเร็วกับการใช้พลังงาน
## 3.Sensor Adaptation: ประโยชน์ของ Adaptive Sampling Rate คืออะไร?
ปรับอัตราการอ่าน sensor ตามสภาพจริง เช่น เร็วขึ้นเมื่อค่าผันผวน ช้าลงเมื่อค่านิ่ง → ประหยัดพลังงานและลดภาระ CPU
## 4.System Health: metrics ใดบ้างที่ควรติดตามในระบบจริง?
ควรติดตาม CPU usage, memory (heap), queue load, task runtime, error count, และ watchdog reset count เพื่อประเมินเสถียรภาพของระบบ


