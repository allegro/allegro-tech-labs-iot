import machine
import utime
import mds18x20
import mwifi
import mntptime

print('Setup code...')
led = machine.Pin(14, machine.Pin.OUT)
led.off()
thermometer = mds18x20.MDS18x20()
wifi = mwifi.WiFi('esp8266labs', 'esp8266labs')
print('Initial time: {}'.format(utime.localtime()))


def print_status(ip, time, temp):
    print('IP: {}, time: {}, temp: {:.2f}.'.format(ip, time, temp))

print('Main loop:')
while True:
    wifi.reconnect()
    mntptime.settime()
    temp = thermometer.get_temperature()
    print_status(wifi.ip(), utime.localtime(), temp)
    if temp >= 30:
        led.on()
    else:
        led.off()
    utime.sleep(1)
