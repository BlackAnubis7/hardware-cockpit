import serial, random, time

mega = serial.Serial('COM4', 115200, timeout=1)
print(mega.in_waiting, mega.out_waiting)
# print(mega.name)
try:
    while(True):
        # r = random.randint(10, 128)
        r = 10
        input()
        mega.write(r.to_bytes(1, 'big') + b'\xF0' * (r-1) + b'\xFC')
        # print(mega.in_waiting)
        x = mega.read(size=256)
        print(f'r={r} ({hex(r)[2:]}) | {x.hex()}', end='')
        time.sleep(0.05)
except KeyboardInterrupt:
    pass

mega.close()
