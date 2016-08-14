# SystemC Exercises
Set of SystemC exercises for the Hardware-Software Project class at UFPB.

## Install SystemC
Fetch the latest stable SystemC version on [http://www.systemc.org/](http://www.systemc.org/) and decompress with tar: `$ tar -xvzf systemc-2.3.1.tgz`

Then, enter in the decompressed folder and run do the following commands:

```
$ mkdir buildsc
$ cd buildsc
$ ../configure
$ make
$ make check
$ make install
```

If there is no error after running above commands, the installation is complete. For finish the environment setup, configure the root Makefile setting your correct SystemC path on `SYSTEMC` variable.

## Running examples
To run the repository examples, just enter on the desired example on the `src/` folder and run `$ make` for build the source. You will be able now to run the `main` executable on console.
