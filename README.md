# mpit

A terminal-based game about hacking.

![](http://i.imgur.com/54B0x1Y.png)

Game emulates it's own terminal, however, I'm trying to make it similar to Unix's one.

![](http://i.imgur.com/P1tWwyT.png)

# Installing

Make sure you have ```gcc``` (of course you have it) and ```python3```. Moreover, you need ncurses and ncursesw developer's libraries. In Debian-based packages you can install them with 
```
# apt-get install libncurses5-dev libncursesw5-dev
```
Compile and install it: 
```
$ ./configure
$ make
# make install
```
To uninstall, run ```# make uninstall```.
