import machine
import utime
import mds18x20
import mwifi
import mntptime
import picoweb

print('Setup code...')
led = machine.Pin(14, machine.Pin.OUT)
led.off()
thermometer = mds18x20.MDS18x20()
wifi = mwifi.WiFi('ArekAP', 'netus369')
wifi.reconnect()


def blink_led():
    led.on()
    utime.sleep(1)
    led.off()

app = picoweb.WebApp(__name__)


@app.route("/")
def index(req, resp):
    yield from picoweb.start_response(resp)
    yield from resp.awrite("Hello world from picoweb running on esp8266.")


@app.route("/blink")
def index(req, resp):
    blink_led()
    yield from picoweb.start_response(resp)
    yield from resp.awrite(';-)')


@app.route("/temp")
def index(req, resp):
    yield from picoweb.jsonify(resp, {'temp': '{:.2f}'.format(thermometer.get_temperature())})


@app.route("/all")
def index(req, resp):
    led.on()
    mntptime.settime()
    ret = {
        'IP': wifi.ip(),
        'Time': utime.localtime(),
        'temp': '{}'.format(thermometer.get_temperature()),
            }
    yield from picoweb.jsonify(resp, ret)
    led.off()

# print('Main loop:')
app.run(debug=True, host="0.0.0.0", port=80)
