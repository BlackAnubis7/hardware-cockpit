import serial

mega = serial.Serial('COM4', 115200, timeout=60)
# print(mega.in_waiting, mega.out_waiting)
# print(mega.name)
ITER = 5
evn = odd = wrg = msd = 0
for i in range(ITER):
    if i % 100 == 0:
        print(i)
    # input()
    if i % 2 == 0:
        mega.write(b'2244668800246822')
    else:
        mega.write(b'1133557799135711')
    x = mega.read(size=8)
    if x == b'99135719':
        odd += 1
    elif x == b'00246828':
        evn += 1
    elif x == b'--------':
        msd += 1
    else:
        # print(x)
        wrg += 1
# msd = ITER - (evn + odd + wrg)
print(f'{evn} EVEN | {odd} ODD | {wrg} WRONG | {msd} MISSED')
mega.close()