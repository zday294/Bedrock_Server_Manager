#http_classes.py

class myRequest:
    verb = ""
    path = ""
    version = ""
    headers = []

    def __init__(self, _verb, _path, _version):
        self.verb = _verb
        self.path = _path
        self.version = _version


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
    headers = []

    content = ""

    def __init__(self, _message, _code, _version, _content):
        self.message = _message
        self.code = _code
        self.version = _version
        self.content = _content
    
    def __str__(self):
        response = f"{self.version} {self.code} {self.message}\n"
        for head in self.headers:
            response += str(head)
            response += '\n'

        response += '\n'
        response += self.content

        return response





#responses
# ok = myResponse("OK", 200)
# page_not_found = myResponse("Page not found", 404)
# bad_request = myResponse("Bad request", 400)


#common headers

htmltype = myHeader("Content-Type", "text/html")

