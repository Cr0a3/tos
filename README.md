I'm# tos
[![Makefile CI](https://github.com/Toni-Graphics/tos/actions/workflows/makefile.yml/badge.svg)](https://github.com/Toni-Graphics/tos/actions/workflows/makefile.yml)

A simple x86_64 os written in C and C++ wich uses the limine bootloader.

### Building
When you want to build tos, you first need to install all nedded dependencys. You can do that via make:
```
sudo make install
```

Then you nee to go into the ``include/limine.h`` file and uncomment it.

Then you can build the main os:
```
make
```
Then the output is in ```tos.iso```.

### Emulating
When you want to emulate this os in qemu, you can chosse many options. 
The simple way is to use make:
```
make run
```
```
make run-hdd
```
```
make run-uefi
```
```
make run-hdd-uefi
```

### License
This reposentory is under the MIT License. More information in the ```LICENSE``` file.

### Countributing
When you want to contribute, read the Contributing Guidlines, join my Discord server and send an DM to me (when i am online, you can find me as the owner).

<a href="https://discord.com/invite/26RxXg8qx3">Invitation to the discord server</a>
