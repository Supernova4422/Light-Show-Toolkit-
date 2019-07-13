# pip3 install paramiko
# pip3 install pysftp
import pysftp
import os
import fileinput
import paramiko
import time
from time import gmtime, strftime


def upload_files(server):
    print("Uploading Files")
    with pysftp.Connection(server[0], username=server[1], password=server[2]) as sftp:
        out_dir = 'Light-Show-Toolkit-/build/src'
        sftp.put_r(server[3], out_dir, confirm=False)


def run_command(command, ssh):
    print("Command: " + command)
    ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command(command + '\n')
    print(ssh_stderr.read())
    print(ssh_stdout.read())


def prepare_pis(server):
    print("-----------------")
    print("Running Commands")
    ssh = paramiko.SSHClient()
    ssh.load_system_host_keys()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(server[0], username=server[1], password=server[2])

    initialise_commands = [
        "sudo apt-get install cmake git libsdl2-dev libsdl2-net-dev libsdl2-mixer-dev libsdl2-2.0;",
        "git clone git://git.drogon.net/wiringPi",
        "cd wiringPi;./build;"
    ]

    prepare_commands = [
        "git clone https://github.com/BKrajancic/Light-Show-Toolkit-.git;",
        "cd Light-Show-Toolkit-;git pull;git pull --recurse-submodules;git submodule update --init --recursive;",
        "cd Light-Show-Toolkit-/;mkdir build;cd build;cmake ../",
        "cd Light-Show-Toolkit-/RF24;sudo ./configure;sudo make all install",
        "cd Light-Show-Toolkit-/build/src/;make all"
    ]

    for command in initialise_commands:
        print("-------")
        run_command(command, ssh)
        print("-------")

    for command in prepare_commands:
        print("-------")
        run_command(command, ssh)
        print("-------")

    print("-----------------")


def run_in_minute(server, lightshow_file, song_file):
    hour = strftime("%H", gmtime())
    minute = (strftime("%M", gmtime()))
    seconds = strftime("%S", gmtime())
    time = str(hour) + ":" + \
        (str(int(minute) + 1).zfill(2)) + \
        ":" + \
        strftime("%S", gmtime())

    print(time)
    cmd = "cd Light-Show-Toolkit-/build/src;sudo ./LightShowProject loadmainfile " + \
        lightshow_file + " startat " + time + " run " + song_file
    ssh = paramiko.SSHClient()
    ssh.load_system_host_keys()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(server[0], username=server[1], password=server[2])
    run_command(cmd, ssh)


if __name__ == "__main__":
    servers = [
        #("10.0.0.50", "pi", "raspberry", "synchroniser/Server_One"),
        ("10.0.0.18", "pi", "raspberry", "synchroniser/Server_Two"),
        ("10.0.0.18", "pi", "raspberry", "synchroniser/Songs")
        # Alternate Directory'build/src/songs/'
    ]

    for server in servers:
        # run_in_minute(server, "Example.lightshow",
        #              "ClappingSounds.wav")

        print("====================================")
        print("Executing on server: " + str(server))
        prepare_pis(server)
        upload_files(server)
        print("====================================")
