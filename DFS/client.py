import socket

class DFS_client:
    def __init__(self):
        # Server IP and port to connect to
        self.host = '127.0.0.1'
        self.port = 8888
        # Create TCP socket
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Connect to the server
        self.client_socket.connect((self.host, self.port))

    def send_command(self, command):
        try:
            self.client_socket.sendall(command.encode())
            response = self.client_socket.recv(4096).decode()
            if not response:
                return "No response from server."
            return response
        except Exception as e:
            return f"Error communicating with server: {e}"

if __name__ == "__main__":
    client = DFS_client()
    while True:
        # Show menu to the user
        print("1. Upload file")
        print("2. Download file")
        print("3. List files")
        print("4. Exit")
        choice = input("Enter choice: ")

        if choice == "1":
            # Upload a file to server
            filename = input("Enter the filename: ")
            content = input("Enter the file content: ")
            command = f"upload {filename} {content}"
            response = client.send_command(command)
            print(response)

        elif choice == "2":
            # Download a file from server
            filename = input("Enter the filename to download: ")
            command = f"download {filename}"
            response = client.send_command(command)
            print(f"File content:\n{response}")

        elif choice == "3":
            # List files on server
            command = "list"
            response = client.send_command(command)
            print(f"Files on server:\n{response}")

        elif choice == "4":
            # Exit the client program gracefully
            command = "exit"
            response = client.send_command(command)
            print(response)
            print("Exiting....")
            break

        else:
            print("Invalid choice. Please try again.")
