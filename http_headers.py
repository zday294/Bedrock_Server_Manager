#http_headers.py

class myheader:
    name = ""
    value = 0

    def __init__(self, _name, _val):
        self.name = _name
        self.value = _val
    

ok = myheader("OK", 200)
page_not_found = myheader("Page not found", 404)
bad_request = myheader("Bad request", 400)

