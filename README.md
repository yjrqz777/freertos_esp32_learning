| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# freertos_esp32_learning

https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/jtag-debugging/index.html#jtag-debugging-examples


https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/jtag-debugging/using-debugger.html#jtag-debugging-using-debugger-command-line


gdbinit:
```
target remote :3333
set remote hardware-watchpoint-limit 2
mon reset halt
maintenance flush register-cache
thb app_main
c
```


openocd -f board/esp32s3-builtin.cfg


xtensa-esp32s3-elf-gdb -x gdbinit build/freertos_esp32_learning.elf


idf.py gdbgui -x gdbinit build/freertos_esp32_learning.elf