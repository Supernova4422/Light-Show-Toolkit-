# pip3 install paramiko
# pip3 install pysftp
import pysftp
import os
import fileinput
import paramiko
import time


def upload_files(server):
    with pysftp.Connection(server[0], username=server[1], password=server[2]) as sftp:
        out_dir = 'Light-Show-Toolkit-/build/'
        with sftp.cd(out_dir):
            in_dir = 'build/src/songs/'
            for filename in os.listdir(in_dir):
                filepath = os.path.join(in_dir, filename)
                print("Uploading: " + filepath)
                sftp.put(filepath)


def run_command(command, ssh):
    print("Command: " + command)
    ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command(command + '\n')
    print(ssh_stderr.read())
    print(ssh_stdout.read())


def prepare_pis(server):

    ssh = paramiko.SSHClient()
    ssh.load_system_host_keys()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(server[0], username=server[1], password=server[2])

    commands = [
        "sudo apt-get install cmake git libsdl2-dev libsdl2-net-dev libsdl2-mixer-dev libsdl2-2.0;",
        "git clone git://git.drogon.net/wiringPi"
        "cd wiringPi;./build"
        "git clone https://github.com/BKrajancic/Light-Show-Toolkit-.git;",
        "cd Light-Show-Toolkit-/;git pull;git pull --recurse-submodules;git submodule update --init --recursive;",
        "cd Light-Show-Toolkit-/;mkdir build;cd build;cmake ../",
        "cd Light-Show-Toolkit-/RF24;sudo ./configure;make all",
        "cd Light-Show-Toolkit-/build/src/;make all"
    ]

    for command in commands:
        print("-------")
        run_command(command, ssh)
        print("-------")


if __name__ == "__main__":
    servers = [
        ("10.0.0.50", "pi", "raspberry"),
        ("10.0.0.18", "pi", "raspberry")
    ]

    for server in servers:
        print("====================================")
        print("Executing on server: " + str(server))
        print("-----------------")
        print("Running Commands")
        prepare_pis(server)
        print("-----------------")
        print("Uploading Files")
        upload_files(server)
        print("====================================")
