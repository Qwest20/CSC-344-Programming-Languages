import subprocess
direct = input("Please enter your directory name.")
output = (subprocess.check_output(["wc", "-1", direct]))
print(output)
