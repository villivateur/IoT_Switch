import socket
import re

HOST, PORT = '', 10082

listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listen_socket.bind((HOST, PORT))
listen_socket.listen(1)
while True:
    client_connection, client_address = listen_socket.accept()
    request = client_connection.recv(1024)
    # print(request.decode())
    request = request.decode()
    action = re.findall("GET /(.+) ", request)
    action = action[0]
    if action=="1" or action=="0":
        f = open("ctrl.in", 'w')
        f.write(action)
        f.close()
        print(action)

    http_response = """
HTTP/1.1 200 OK

<a href="/1">ON</a><br/><a href="/0">OFF</a>
"""
    client_connection.sendall(http_response.encode())
    client_connection.close()