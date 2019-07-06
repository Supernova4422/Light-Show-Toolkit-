# pip install paramiko
from ftplib import FTP
import os
import fileinput
import paramiko
import time

# Send all files


server = "10.0.0.50"
username = "pi"
password = "raspberry"
servers = [(server, username, password)]


def sync_files(servers):
    ftp = FTP()
    ftp.set_debuglevel(2)
    for server in servers:
        ftp.connect(server[0], 21)
        ftp.login(server[1], server[2])
        ftp.cwd('/')

        for filename in os.listdir('../build/src/songs/'):
            fp = open(filename, 'rb')
            ftp.storbinary('STOR %s' % os.path.basename(filename), fp, 1024)
            fp.close()


ssh = paramiko.SSHClient()
ssh.load_system_host_keys()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect(server, username=username, password=password)

ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command(
    "sudo apt-get install cmake git libsdl2-dev libsdl2-net-dev libsdl2-mixer-dev libsdl2-2.0" + '\n')
print(ssh_stderr.read())
print(ssh_stdout.read())
print("")

ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command(
    "git clone https://github.com/BKrajancic/Light-Show-Toolkit-.git;  " + '\n')
print(ssh_stderr.read())
print(ssh_stdout.read())
print("")

ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command(
    "cd Light-Show-Toolkit-/;git pull;git submodule update --init --recursive;git pull --recurse-submodules")
print(ssh_stderr.read())
print(ssh_stdout.read())
print("")

ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command(
    "cd Light-Show-Toolkit-/;mkdir build;cd build;cmake ../" + '\n')
print(ssh_stderr.read())
print(ssh_stdout.read())
print("")

ssh_stdin.close()


#channel = ssh.get_transport().open_session()

# channel.get_pty()         # get a PTY
# channel.invoke_shell()    # start the shell before sending commands
#channel.send("git clone https://github.com/BKrajancic/Light-Show-Toolkit-.git")

# print(channel.recv(1024))
# Other commands you must run
#"sudo apt-get install git"
