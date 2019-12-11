# PVSafeOFField

A ParaView plugin to save cell data in ASCII OpenFOAM field format. The plugin is described in the paper **A flexible workflow for simulating transcranial electric stimulation in healthy and lesioned brains** by *Benjamin Kalloch, Pierre-Louis Bazin,  Arno Villringer, Bernhard Sehm, and Mario Hlawitschka*.

## How to compile
1. Set up the ParaView environment as described in [1] 
2. Create a folder "build"
3. In the "build" folder execute `cmake ..`
4. Run `make`
5. In ParaView, load the compiled plugin dynamic library (the so-file) under `Tools -> Manage Plugins -> Load New`

###### Useful links
[1] Set up the ParaView environment: https://openfoam.org/download/source/third-party-software/
