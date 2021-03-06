# SystemC Exercises
Set of SystemC exercises for the Hardware-Software Project class at UFPB.

## Install SystemC
Fetch the latest stable SystemC version on [http://accellera.org/downloads/standards/systemc](http://accellera.org/downloads/standards/systemc) and decompress with tar: `$ tar -xvzf systemc-2.3.1.tgz`

Then, enter in the decompressed folder and run do the following commands:

```
$ mkdir buildsc
$ cd buildsc
$ ../configure
$ make
$ make check
$ make install
```

If there is no error after running above commands, the installation is complete. For finish the environment setup, configure the Makefile on the root of this repository, setting your correct SystemC path on `SYSTEMC_HOME` variable.

## Running examples
Configure the `SYSTEMC_HOME` environment variable with the SystemC installation path:

```
$ export SYSTEMC_HOME=<your_systemc_path>
```

Then, to run the repository binaries, just enter on the desired example on the `src/` folder and run `$ make` for build the source. You will be able now to run the `main` or `run_verification` executables on console.
