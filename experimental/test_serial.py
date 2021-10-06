import serial

mega = serial.Serial('COM4', 115200, timeout=60)
print(mega.in_waiting, mega.out_waiting)
# print(mega.name)
while(True):
    input()
    print(mega.write(b'123'))
    x = mega.read(size=3)
    print(x)
mega.close()