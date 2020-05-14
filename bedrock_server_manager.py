# Bedrock Server Manager
# Zach Day, [further authors here]
# bedrock_server_manager.py

import socket
import io
import sys
import os
import http_classes
import datetime
# import ctypes


port = 8080

# httplib = ctypes.cdll.LoadLibrary("./httplib.so")

def log(message: str): 
    date = datetime.datetime.now()
    print(f"{date.month}-{date.day}-{date.year} {date.hour}:{date.minute}:{date.second}    {message}")


def parseHttp(sock, client) -> http_classes.myRequest: 
    requestLine = sock.recv(1024).decode()
    log(f"Received mesage '{requestLine}' from client {client}")


    verbage, headers = requestLine.split("\n")
    print(verbage)
    print(headers)

    # request = http_classes.myRequest()


def handleClient(sock: socket):

    workersock, clientaddr = sock.accept()

    log(f"Connection from {clientaddr}")
    initial = workersock.recv(1024)
    log(f"Message from {clientaddr}: {initial.decode()}")

    file = open("home.html", 'r')
    page = file.read()

    #print(page)
    
    workersock.send(str(http_classes.myResponse("OK", 200, "HTTP/1.1", page)).encode())

    # workersock.send(str(http_classes.ok).encode())
    # workersock.send(str(http_classes.htmltype).encode())
    # workersock.send(b'\n')
    # workersock.sendfile(page)
    log("Sent file: homepage.html")



    # begin page handler here
    log(f"Working with client {clientaddr}")
    while True:
        req = parseHttp(workersock, clientaddr)



 





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