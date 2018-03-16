## _System V IPCs Code Sample_
##### _What is this?_

System V IPCs are not POSIX IPCs, and, as such, harder to find explanations for, except amidst a very arduous and / or ancient project. As such, I want to provide here a very basic program making a concrete use of those system calls.

##### _What does this do?_

A given number of trains have to cross a bridge. It is not strong enough to allow all of them to cross at the same time, so some have to wait before continuing. When all trains have passed, the program exits.

##### _How does it work?_

The railroads are stored in a **shared memory** segment, the trains use a single **semaphore** to try and cross the bridge. They send their current position through a **message queue**, but still update it themselves in the **shared memory segment**.
The main process will be the one which will try to print the current positions based on one method or another. Simply put, you will find in include/ipcs_defines.h a macro called **USE_SHM**, set to 0 by default. The main process will look at it and use the shared memory or the message queue accordingly.

To compile, simply run:
```sh
make
```
To recompile:
```sh
make re
```
And to launch it:
```sh
trains `pwd`
```
This will make **ftok()** create a key from the current directory. But if you don't want to, or if the current directory is under use, simple replace the argument with any other ***existing*** file / directory.

The amount of trains, the number of which can cross at the same time, and the layout of the railroads can be changed by modifiying the macros in "ipcs_defines.h":
1. **NB_TRAINS** defines the total amoun of trains.
2. **NB_RAILWAYS** is the amount of trains who can cross the bridge at the same time.
3. **BRIDGE_BEG** makes the bridge start at the BRIDGE_BEGth character.
4. **BRIDGE_END** makes the bridge end at the BRIDGE_ENDth character.
5. **TOTAL_SIZE** is the total size of the bridge.

You shouldn't have to modify the last 3, but it is possible if you want to.

#### _The program keeps rambling about a semaphore / shared memory segment / message queue already created_

This means that the path trains was given is already under use by one or several IPC(s). There may be several causes:
- The path is used as a key by a different program. Simply select another.
- If you have not modified the code and the statement above is false, then an error occurred while creating one of the IPC. during a previous launch of trains. Look below to see what you can do.
- If you have modified the code and the first statement is false, the second may still be true. Or, you have modified the handling of IPCs and forgotten to remove one. Look below to see what you can do.

You can see your current IPCs with the shell command
```sh
ipcs
```
And remove a specific IPC with
```
ipcrm
```
Most of the time, you will have single semapore, and / or message queue. They will probably the the one causing all the trouble. For the shared memory, it will very often be the only segment attached to no process (see under the _nattch_ column)
***However, make sure you know what you are doing before removing an IPC*** (I could not stress this enough).