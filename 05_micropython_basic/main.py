import machine
import utime

print('Setup code...')
led = machine.Pin(14, machine.Pin.OUT)

print('Main loop:')
# while True:
for ii in range(5):
    led.on()
    utime.sleep(1)
    led.off()
    utime.sleep(2)
    print('Still in main loop')

print("This line won't be printed")
