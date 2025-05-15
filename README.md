# Software_I2C

### Працює на:

* STM32F411CEU6

### Основні функції:

* `I2C_Init()` — ініціалізує GPIO для I2C (SDA та SCL)
* `I2C_Start()` / `I2C_Stop()` — формує стартову та стоп-умову I2C
* `I2C_WriteByte(byte)` — надсилає байт даних
* `I2C_ReadByte(ack)` — читає байт з можливістю ACK/NACK
* `TSL2561_PowerOn()` — вмикає живлення TSL2561 (встановлює регістр керування)
* `TSL2561_ReadData()` — читає виміряне значення освітленості

### Відтестовано з:

* Давачем освітленості TSL2561
* Зв'язок перевірений через `SCL` та `SDA` на GPIOB

### Дефайни:

* `TSL2561_ADDR_WRITE` — адреса для запису (0x72)
* `TSL2561_ADDR_READ` — адреса для читання (0x73)
* `CMD_BIT` — 0x80, вказує, що операція адресує регістр

### Приклад:

* Прийняте значення в темному середовищі:
![image](https://github.com/user-attachments/assets/7b2da330-11a8-4534-ace0-57dde483b146)

* Прийняте значення в світлому средовищі:
![image](https://github.com/user-attachments/assets/2a36df88-1c0d-4af1-9c5b-fcda59cd099e)

