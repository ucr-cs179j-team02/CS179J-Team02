
import os
from http.server import BaseHTTPRequestHandler, HTTPServer


host_name = '192.168.1.211'    # machines IP
host_port = 8070

status = ''
class MyServer(BaseHTTPRequestHandler):

    def do_HEAD(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        """ do_GET() can be tested using curl command 
            'curl http://server-ip-address:port' 
        """

        self.do_HEAD()
            #status = ''
        if self.path=='/far':
            #turn off the sprayer
            status = 'Far - no one is visible'
        elif self.path=='/close1':
            # we see someone but not within 6ft
            status = 'Sees person beyond 6 feet'
        elif self.path=='/close2Left':
            #we see someone within 6 feet no mask on the left
            status = 'sees someone within 6ft on left'
        elif self.path=='/close2Right':
            #we see someone within 6 feet no mask on the right
            status = 'sees someone within 6ft on right'
        elif self.path=='/close3Left':
            #we see someone within 3 feet no mask on the left
            status = 'sees someone within 3ft on left'
        elif self.path=='/close3Right':
            #we see someone within 3 feet no mask on the right
            status = 'sees someone within 3ft on right'
        else:
            #turn off
            status = 'Else triggered -off'

        print(status)
        #self.wfile.write(status)


if __name__ == '__main__':
    http_server = HTTPServer((host_name, host_port), MyServer)
    print("Server Starts - %s:%s" % (host_name, host_port))

    try:
        http_server.serve_forever()
    except KeyboardInterrupt:
        http_server.server_close()
