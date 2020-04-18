Author: Tim Lindquist (Tim.Lindquist@asu.edu), ASU Polytechnic, CIDSE, SE
Version: April 2020

See http://pooh.poly.asu.edu/Mobile
See http://pooh.poly.asu.edu/Ser321

Purpose: demonstrate Json-RPC with server in CPP, and command-line clients
in both languages. The stubs for CPP are created using libjson-rpc-cpp, and the
Java stub is manually created using java.net.HttpURLConnection class.
The server and terminal clients are executable on both MacOS and Debian Linux.

Communication between the service and its clients is done using JSON-RPC.
The purpose of the example is to demonstrate JSON and JSON-RPC. Reference
the following sources for background on these technologies:

JSON (JavaScript Object Notation):
 http://en.wikipedia.org/wiki/JSON
 The JSON web site: http://json.org/

JSON-RPC (JSON Remote Procedure Call):
 http://www.jsonrpc.org
 http://en.wikipedia.org/wiki/JSON-RPC

Building and running the server and terminal clients is done with Ant.
This example depends on the following frameworks:
1. Ant
   see: http://ant.apache.org/
2. Json for Java as implemented (reference) by Doug Crockford.
   See: https://github.com/stleary/JSON-java
3. Using the package manager apt-get, install the C++ JsonRPC and jsoncpp frameworks
   See the course page for instructions, and follow the build instructions for C++:
   http://pooh.poly.asu.edu/Ser321/Resources/buildVB.html

To build and run the examples, you will need to have Ant installed on
your system, with the target extensions for building C++
(see the CppFraction example from unit1).

ant build.server   // build the cpp server
./bin/studentRPCServer 8080 // to execute the server

The C++ JsonRPC framework generates server and client-side proxies based on the methods that are
described using Json in the file: StudentLibraryMethods.json
See the Class Notes on Object-Based Client-Server Communications and the C++ framework usage
described at:
https://github.com/cinemast/libjson-rpc-cpp

To execute the client, start a new terminal in the same folder:
ant build.java.client
execute the java client with the command:
java -cp classes:lib/json.jar sample.student.client.StudentCollectionClient localhost 8080

To execute the client, start a new terminal in the same folder:
ant build.client   // build the cpp client
./bin/studentRPCClient http://localhost:8080   // to run the client.

You should run the server on your Raspberry Pi and the clients on your Virtual Box Debian.
When doing so, the host name or ip for the Raspberry Pi should be used when invoking clients.

To clean the project directory:
ant clean

The project directory also includes scripts to demonstrate one approach that
can be used to run a processes in the background on either
linux or MacOS. This allows you to start up a server on your Raspberry Pi,
then to log off of the RPi and have the server continue to run until the system
goes down, or you log in again to stop the service. The approach shown in this
project directory is preferred unless you want the service to start-
up automatically everytime the system is re-booted. If so, then use the system-specific
mechanism for creating a service. Linux uses the files in /etc/init.d as start-ups for
services.

Running a program in the background, and allowing it to continue after you log off.

To do this, you should provide execute permission to the shell script accompanying
this example (the jar tool strips them off).
chmod u+x background.sh
You will find this bourne shell (/bin/sh) script in the project base directory.
This is a shell program, or command files. You can use it to start, stop or resart
a server to run in the background. It also redirects output to a log file.
The script assigns the standard output, error, and input streams
(stdin, stderr, and stdout) to files. To start the server in the background run:
./background.sh start ./bin/calculateRPCServer 8080
  
After executing this command script, the server will run in the background until you kill it
manually, or use the script again to restart or stop the process.
To see its status, and get the information needed to kill it (PID), use the ps command:
ps
which will show you a listing of your active programs. The process id (PID) of each
running program will be shown on the left, and the command that started is shown as
the last string displayed. To terminate a running program, you can use:
kill -9 pid
the -9 is a signal to the process indicating it should not ignore the kill.

You can stop the background process with:
./background.sh stop
and while it is running cause it to be restarted with:
./background.sh restart

The background script writes files to the folder ./log, placing the
command to start the server in the file log/command.txt. Standard output goes to the
file ./log/log.txt. Error messages to the file log/error.txt. Standard input for the
program is taken from a null device, a opposed to the console/terminal.
Use this same script to stop or restart the program with:
./background.sh stop
./background.sh restart
When using either of these scripts, you will find the output of the server logged to files:
log.txt (for backgroundStart.sh) and log/log.txt (for background.sh). There are also error logs.

If you don't use one of this script, you may experience servers being stopped, but not
terminated. Thus, when you try to start them again, the new process won't be able to
attach to the requested port because its already being used by a prior invocation of the
server. When you run a server manually, as shown above, you must terminate it using the
shell ps (process status) and kill commands, as explained above.

end
