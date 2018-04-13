import time
import machine
import onewire
import ds18x20


# based on http://docs.micropython.org/en/latest/esp8266/esp8266/quickref.html#onewire-driver
class MDS18x20:
    def __init__(self):
        # create the onewire object
        self.ds = ds18x20.DS18X20(onewire.OneWire(machine.Pin(2)))
        self.rom = self.ds.scan()[0]

    def get_temperature(self):
        self.ds.convert_temp()
        time.sleep_ms(1000)
        temperature = self.ds.read_temp(self.rom)
        return temperature
