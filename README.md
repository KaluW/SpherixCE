# Spherix
SpherixCE is a puzzle game programmed from scratch in C using the CE development toolchain.

## Gameplay
![Screenshot](https://raw.githubusercontent.com/kaluw/spherixce/master/extra/gameplay.gif)

## Build
To build SpherixCE, make sure to have the latest [CE C Toolchain](https://github.com/CE-Programming/toolchain/releases/latest) installed.

Then simply clone or download the repository from above, and run the following in the terminal:

    make gfx
    make

The following files will be created and should be sent to the calculator:

   `src/gfx/SpherixS.8xv`: SpherixCE sprites

   `src/gfx/SpherixT.8xv`: SpherixCE tileset

   `bin/SPHERIX.8xp`: SpherixCE program
   
## Run
From the homescreen of the calculator, run ```Asm(prgmSPHERIX)```.

## Controls

   `arrow keys`: move player
   
   `[clear]`: exit program
   
## Help
If you have issues building the program or find bugs in the code, feel free to submit your issue [here](https://www.cemetech.net/forum/viewtopic.php?p=290460#290460). Otherwise open a new issue in this repository.
