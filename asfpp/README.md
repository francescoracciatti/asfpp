## Install
To install ASF++ type:
```
> ./makemake
> make
```

Read the Installation guide for more details.


## Package structure
In the Root directory there are the following contents:
* **Simulations** contains various simulation configuration files, Simulations can easily be run from its sub dirs.
* **interpreter** contains the Python interpreter to interpret the attack descriptions into XML files.
* **src** contains the source code of ASF++.
* **makemake** generates the appropriate Makefiles. It uses the OMNeT++' opp_makemake tool.