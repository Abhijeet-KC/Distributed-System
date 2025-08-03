import socket
import threading
import os

class DFS:
    def __init__(self):
        # Server IP and port to listen on
        self.host = '127.0.0.1'
        self.port = 8888
        # Directory to save files
        self.base_directory = 'data'
        self.server_socket = None
        # List to keep track of connected clients
        self.clients = []
    
    def start(self):
        # Create TCP socket
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Bind the socket to the IP and port
        self.server_socket.bind((self.host, self.port))
        # Start Listening, max 5 clients waiting
        self.server_socket.listen(5)
        print(f"Server listening on {self.host}:{self.port}")
        # Create data directory if it doesn't exist
        if not os.path.exists(self.base_directory):
            os.makedirs(self.base_directory)
        # Infinite loop to accept clients
        while True:
            client_socket, client_address = self.server_socket.accept()
            print(f"Accepted connection from {client_address}")
            self.clients.append(client_socket)
            # Create a new thread for each connected client
            client_thread = threading.Thread(target=self.handle_client, args=(client_socket,))
            client_thread.start()

    def handle_client(self, client_socket):
        # Handle commands from a single client
        while True:
            try:
                # Receive data from client (max 1024 bytes)
                data = client_socket.recv(1024).decode()
                if not data:
                    # No data means client disconnected
                    break
                
                # Split command and arguments
                command, *args = data.split()
                
                # Handle exit command first
                if command.lower() == 'exit':
                    client_socket.sendall("Goodbye!".encode())
                    break  # Exit the loop to close connection
                
                if command.lower() == 'upload':
                    # Expect filename and file content after upload command
                    filename = args[0]
                    file_content = " ".join(args[1:])
                    self.save_file(filename, file_content)
                    client_socket.sendall("Upload successful".encode())

                elif command.lower() == 'download':
                    # Expect filename after download command
                    filename = args[0]
                    file_content = self.read_file(filename)
                    client_socket.sendall(file_content.encode())

                elif command.lower() == 'list':
                    # Send the list of files in the data directory
                    file_list = "\n".join(self.get_file_list())
                    client_socket.sendall(file_list.encode())

                else:
                    # Invalid command received
                    client_socket.sendall("Invalid Command".encode())

            except Exception as e:
                print(f"Error: {e}")
                break
        
        # Remove client from list and close socket after disconnect
        client_socket.close()
        if client_socket in self.clients:
            self.clients.remove(client_socket)

    def save_file(self, filename, content):
        # Save the file content to a file inside data directory
        filepath = os.path.join(self.base_directory, filename)
        with open(filepath, 'w') as file:
            file.write(content)

    def read_file(self, filename):
        # Read the content of the requested file and return it
        filepath = os.path.join(self.base_directory, filename)
        try:
            with open(filepath, 'r') as file:
                return file.read()
        except FileNotFoundError:
            return "File not found."

    def get_file_list(self):
        # Return a list of files in the data directory
        return os.listdir(self.base_directory)

if __name__ == "__main__":
    server = DFS()
    server.start()
