import machine
import utime
import mds18x20

print('Setup code...')
led = machine.Pin(14, machine.Pin.OUT)
led.off()
thermometer = mds18x20.MDS18x20()

print('Main loop:')
while True:
    temp = thermometer.get_temperature()
    print('Current temperature: {:.2f}'.format(temp))
    if temp >= 30:
        led.on()
    else:
        led.off()
    utime.sleep(1)
