from sys import argv
from datetime import datetime
import socket

HOST = "127.0.0.1"
PORT = 8080

logging = 0
for i in range(0, len(argv)):
    if argv[i] == "-l":
        logging = 1
        logfile = argv[i+1]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(1)

data = []

if logging:
    logfile = open(logfile, "a+")

connectedips = []

while True:
    cc, ca = s.accept()
    req = cc.recv(1024).decode()
    if logging:
        now = datetime.now()
        now = now.strftime("%d/%m/%Y %H:%M:%S")
        if req == "GETDATA":
            if ca[0] in connectedips:
                pass
            else:
                logfile.write("{} {} CONNECTED\n".format(now, ca[0]))
        else:
            logfile.write("{} {} {}\n".format(now, ca[0], req))
    if req == "GETDATA":
        tosend = "\n".join(data)
        cc.sendall(tosend.encode())
        if not ca[0] in connectedips:
            connectedips.append(ca[0])
    else:
        data.append(req)
    cc.close()
