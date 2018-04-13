import machine
import mwifi
import picoweb

print('Setup code...')
wifi = mwifi.WiFi('esp8266labs', 'esp8266labs')
wifi.reconnect()
while not wifi.is_connected():
    wifi.reconnect()

led = machine.Pin(14, machine.Pin.OUT)
message = {'Status': 'Off'}
led.on()

app = picoweb.WebApp(__name__)


@app.route("/")
def index(req, resp):
    yield from picoweb.start_response(resp)
    yield from resp.awrite("Hello world from picoweb running on esp8266.")


@app.route("/switch")
def index(req, resp):
    if message['Status'] is "On":
        led.on()
        message['Status'] = "Off"
    elif message['Status'] is "Off":
        led.off()
        message['Status'] = "On"
    else:
        led.on()
        message['Status'] = "Unknown"

    yield from picoweb.jsonify(resp, '{}'.format(message))


@app.route("/status")
def index(req, resp):
    yield from picoweb.jsonify(resp, '{}'.format(message))


app.run(debug=True, host=wifi.ip(), port=80)
