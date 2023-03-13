from SimConnect import *

def get(s: str):
    global aq
    s = s.replace(' ', '_').upper()
    result = aq.get(s)
    out = str(result)
    try:
        if int(result) == result:
            out += ' ' + '(0b{0:b})'.format(int(result))
    except:
        pass
    print(s + ': ' + out)

sm = SimConnect()
aq = AircraftRequests(sm, _time=2000)
ae = AircraftEvents(sm)

# aq.set('ENGINE_CONTROL_SELECT', 0b01)
while True:
    inp = input()
    if inp != '':
        # get(inp)
        try:
            thr = float(inp) * 163.83
            event_to_trigger = ae.find("AXIS_THROTTLE_SET")
            event_to_trigger(int(thr))
        except ValueError:
            pass
