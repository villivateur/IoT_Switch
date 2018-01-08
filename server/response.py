import socket

HOST, PORT = '', 10081
listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listen_socket.bind((HOST, PORT))
listen_socket.listen(1)

while True:
    client_connection, client_address = listen_socket.accept()
    req = client_connection.recv(1024)
    print req
    resp = "0"
    client_connection.sendall(str(resp))
    client_connection.close()
