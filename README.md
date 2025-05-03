# TCP-Port-Scanner

A simple command-line tool that scans a range of ports on a given IP address to find out which ports are open.

This program tries to connect to each port you specify on a target IP address. If the connection is successful, it prints that the port is open.

To compile the program, use gcc -o portscanner portscanner.c, then run it with ./portscanner and follow the prompts.

This project is intended for educational use and local network testing only. Do not scan devices or servers you do not own or have permission to test.
