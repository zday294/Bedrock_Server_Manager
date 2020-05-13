#http_classes.py

class myHeader:
    name = ""
    value = ""

    def __init__(self, _name, _val):
        self.name = _name
        self.value = _val

    def __str__(self):
        return f"{self.name}: {self.value}\n"
    

class myResponse:
    message = ""
    code = 0
    version = "HTTP/1.1"

    def __init__(self, _message, _code, _version="HTTP/1.1"):
        self.message = _message
        self.code = _code
        self.version = _version
    
    def __str__(self):
        return f"{self.version} {self.code} {self.message}\n"





#responses
ok = myResponse("OK", 200)
page_not_found = myResponse("Page not found", 404)
bad_request = myResponse("Bad request", 400)


#common headers

htmltype = myHeader("Content-Type", "text/html")

