import network
import utime


class WiFi(object):
    def __init__(self, wifi_sid, wifi_pass):
        self.wifi_sid = wifi_sid
        self.wifi_pass = wifi_pass
        self.wlan = network.WLAN(network.STA_IF)

    def reconnect(self):
        if not self.wlan.isconnected():
            print('Connecting to network...')
            self.wlan.active(True)
            self.wlan.connect(self.wifi_sid, self.wifi_pass)
            while not self.wlan.isconnected():
                # print(self.wlan.status())
                # print('STAT_IDLE – no connection and no activity,')
                # print('STAT_CONNECTING – connecting in progress,')
                # print('STAT_WRONG_PASSWORD – failed due to incorrect password,')
                # print('STAT_NO_AP_FOUND – failed because no access point replied,')
                # print('STAT_CONNECT_FAIL – failed due to other problems,')
                # print('STAT_GOT_IP – connection successful.')
                print('Network config:', self.wlan.ifconfig())
                utime.sleep(1)
            print('Network config:', self.wlan.ifconfig())

    def is_connected(self):
        return self.wlan.isconnected()

    def ip(self):
        if self.wlan.isconnected():
            return self.wlan.ifconfig()[0]
        else:
            return 'Not connected'

    def status(self):
        return self.wlan.status()
