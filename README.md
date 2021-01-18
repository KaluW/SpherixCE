# Spherix
SpherixCE is a puzzle game programmed from scratch in C using the CE development toolchain.

## Build
To build SpherixCE, make sure to have the latest [CE C Toolchain](https://github.com/CE-Programming/toolchain/releases/latest) installed.

Then simply clone or download the repository from above, and run the following in command line:

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