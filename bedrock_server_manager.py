# Bedrock Server Manager
# Zach Day, [further authors here]
# bedrock_server_manager.py

import socket
import io
import sys
import os
import http_headers
import datetime
import ctypes

port = 8080


def log(message: str):
    date = datetime.datetime.now()
    print(f"{date.month}-{date.day}-{date.year} {date.hour}:{date.minute}:{date.second}    {message}")





def handleClient(sock: socket):

    workersock, clientaddr = sock.accept()

    log(f"Connection from {clientaddr}")

    page = open("home.html", 'rb')

    workersock.send(b'HTTP/1.1 200 OK\n\n')
    workersock.sendfile(file)

    # begin page handler here

    









def runServer():
    print("Entered main")


    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sock.bind(('', port))
    log(f"Listening on {port}")
    sock.listen(1)
    
    while True:
        handleClient(sock)



    


if __name__ == "__main__":
    print("""Minecraft Bedrock Server Manager\nby Zachary Day\nCopyright 2020\n""")
    runServer()