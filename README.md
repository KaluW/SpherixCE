# SpherixCE
SpherixCE is a puzzle game programmed from scratch in C using the CE development toolchain.

## Building
If you would like to build SpherixCE, be sure you have the latest LLVM [CE C Toolchain](https://github.com/CE-Programming/toolchain/releases/latest) installed.

Then simply clone or download the repository from above, and run the following commands:

    make gfx
    make

The following files make up the built project, which should be sent to the calculator:

   `bin/Spherix.8xp`: SpherixCE program

   `src/gfx/SpherixS.8xv`: SpherixCE sprites

   `src/gfx/SpherixT.8xv`: SpherixCE tileset
