# Spherix
SpherixCE is a puzzle game programmed from scratch in C using the CE development toolchain.

## Build
If you would like to build SpherixCE, be sure you have the latest LLVM [CE C Toolchain](https://github.com/CE-Programming/toolchain/releases/latest) installed.

Then simply clone or download the repository from above, and run the following in command line:

    make gfx
    make

The following files make up the built project, which should be sent to the calculator:

   `src/gfx/SpherixS.8xv`: SpherixCE sprites

   `src/gfx/SpherixT.8xv`: SpherixCE tileset

   `bin/SPHERIX.8xp`: SpherixCE program
   
## Controls

   `arrow keys`: move player
   
   `[clear]`: exit program