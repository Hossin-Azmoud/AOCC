#!/bin/python3

from os import scandir, system

CC="gcc"
CFLAGS="-Wall -Wextra -pedantic -Werror"

def main():
    print("[*] Making the bin directory.")
    system("mkdir -p bin")
    dir = scandir('.')
    for entry in dir:
        name = entry.name
        if name.endswith(".c"):
            bin_name = name.split(".")[0]
            out = f"./bin/{bin_name}"
            command = f"{CC} {CFLAGS} -o {out} {name}"
            print(f"[BUILDING] {name} -> {out}")
            print(f"[CMD] {command}")
            system(command)
main()
