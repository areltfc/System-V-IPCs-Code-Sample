## _System V IPCs Code Sample_
##### _What is this?_

System V IPCs are not POSIX IPCs, and, as such, harder to find explanations for, except amidst a very arduous and / or ancient project. As such, I want to provide here a very basic program making a concrete use of those system calls.

##### _What does this do?_

A given number of trains have to cross a bridge. It is not strong enough to allow all of them to cross at the same time, so some have to wait before continuing. When all trains have passed, the program exits.

##### _How does it work?_

The railroads are stored in a **shared memory** segment, the trains use a single **semaphore** to try and cross the bridge (**message queues** will soon be implemented).

To compile, simply run:
```sh
gcc src/*.c -I include -o trains
```
And to launch it:
```sh
trains `pwd`
```
This will make **ftok()** create a key from the current directory. But if you don't want to, or if the current directory is under use, simple replace the argument with any other ***existing*** file / directory.

The amount of trains, the number of which can cross at the same time, and the layout of the railroads can be changed by modifiying the macros in "ipcs_tests.h":
1. NB_TRAINS defines the total amoun of trains.
2. NB_RAILWAYS is the amount of trains who can cross the bridge at the same time.
3. BRIDGE_BEG makes the bridge start at the BRIDGE_BEGth character.
4. BRIDGE_END makes the bridge end at the BRIDGE_ENDth character.
5. TOTAL_SIZE is the total size of the bridge.

You shouldn't have to modify the last 3, but it is possible if you want to.

#### _The program keeps rambling about a semaphore / shared memory segment / message queue already created_

**If you have modified the code**, then the likeliest cause is that you have forgotten to remove an IPC.
You can see your current IPCs with the shell command
```sh
ipcs
```
And remove a specific IPC with
```
ipcrm
```
But make sure you know what you are doing before removing an IPC.