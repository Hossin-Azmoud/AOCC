#!/bin/python3

from os import scandir, system

CC="gcc"
CXX="g++"
# CFLAGS="-Wall -Wextra -pedantic -Werror"
CFLAGS="-Wno-deprecated"
cpp = 0
c   = 0
def main():
    print("[*] Making the bin directory.")
    system("mkdir -p bin")
    dir = scandir('.')
    for entry in dir:
        name = entry.name
        c   = name.endswith(".c")
        cpp = name.endswith(".cpp")
        if c or cpp:
            bin_name = name.split(".")[0]
            out = f"./bin/{bin_name}"
            lib = ""
            if name == "04.c":
                lib = "-lm"
            if cpp:
                command = f"{CXX} {CFLAGS} -o {out} {name} {lib}"
            else:
                command = f"{CC} {CFLAGS} -o {out} {name} {lib}"
            print(f"[BUILDING] {name} -> {out}")
            print(f"[CMD] {command}")
            system(command)
main()
