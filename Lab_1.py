import os
def process_management():
print("\n--- Process Management ---")
pid = os.fork()
if pid == 0:
# Child process
print("Child Process")
print("Child PID :", os.getpid())
print("Parent PID :", os.getppid())
os._exit(0)
else:
# Parent process
print("Parent Process")
print("Parent PID :", os.getpid())
os.wait()
print("Child process completed.")
def file_management():
print("\n--- File Management ---")
filename = "sample.txt"
# Create/Open file
fd = os.open(filename, os.O_CREAT | os.O_RDWR | os.O_TRUNC, 0o644)
print("File opened successfully.")
# Write data
data = b"Hello, this is UNIX file management."
os.write(fd, data)
print("Data written successfully.")
# Move file pointer to beginning
os.lseek(fd, 0, os.SEEK_SET)
# Read data
read_data = os.read(fd, 100)
print("Data read from file:")
print(read_data.decode())
# Close file
os.close(fd)
print("File closed successfully.")
def input_output():
print("\n--- Input/Output System Calls ---")
message = input("Enter a message: ")
os.write(1, b"You entered: ")
os.write(1, message.encode())
os.write(1, b"\n")
def main():
while True:
print("\n========== UNIX SYSTEM CALLS ==========")
print("1. Process Management")
print("2. File Management")
print("3. Input/Output")
print("4. Exit")
choice = int(input("Enter your choice: "))
if choice == 1:
process_management()
elif choice == 2:
file_management()
elif choice == 3:
input_output()
elif choice == 4:
print("Program terminated.")
break
else:
print("Invalid choice!")
if __name__ == "__main__":
main()