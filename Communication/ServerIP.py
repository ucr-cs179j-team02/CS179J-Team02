import os

import serial
from http.server import BaseHTTPRequestHandler, HTTPServer


host_name = '192.168.1.68'    # machines IP
host_port = 8070
ser = serial.Serial('COM3', 9600)
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
            
        if self.path == '/inSight':
            status = 'Sees an unmasked person'
            val = "2"
        elif self.path == '/center':
            status = 'Sees person in the center'
            val = "3"
        elif self.path == '/left':
            status = 'Sees person in the left'
            val = "4"
        elif self.path == '/right':
            status = 'Sees person in the right'
            val = "5"
        elif self.path == '/shoot':
            status = 'Triggers spray'
            val = "6"
        else:
            status = 'Else triggered -off'
            val = "1"

        print(val + '-' + status)
        #for i in range(2):
        ser.write(val.encode())
            #time.sleep(0.26)

        #print(ser)

if __name__ == '__main__':
    http_server = HTTPServer((host_name, host_port), MyServer)
    print("Server Starts - %s:%s" % (host_name, host_port))

    try:
        http_server.serve_forever()
    except KeyboardInterrupt:
        http_server.server_close()

    #ser = serial.Serial('COM3',9600)
    #while 1:
    #    ser.write(self.path.encode())
