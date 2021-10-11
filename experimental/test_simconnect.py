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

aq.set('ENGINE_CONTROL_SELECT', 0b01)
while True:
    inp = input()
    if inp != '':
        get(inp)
