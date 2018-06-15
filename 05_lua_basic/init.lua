print('Setup code...')
local pin = 2 -- GPIO4
local status = gpio.LOW
local duration = 5000 -- ms

gpio.mode(pin, gpio.OUTPUT)
gpio.write(pin, status)

tmr.alarm(0, duration, 1, function ()
    if status == gpio.LOW then
	print("Led On")
        status = gpio.HIGH
    else
	print("Led Off")
        status = gpio.LOW
    end

    gpio.write(pin, status)
end)
