# ASF++
The Attack Simulation Framework makes it possible to simulate the impact of cyber-physical attacks 
on WSNs. 

Thanks to ASF, the user can describe attacks, and evaluate their impact, 
on the network and the application. 

**Under porting** from Castalia 3.2 to Castalia 3.3.   

## Description
ASF++ is composed by three elments:
 + an Attack Description Language (ADL);
 + an Attack Description Interpreter (ADI);
 + an Attack Simulator.

### Attack Description Language
ADL is a high-level and user friendly description language that provides users with the capability of describe the 
effects of cyber-physical attacks on the network or the application.

### Attack Description Interpreter
ADI is the 'glue' between ADL and the underlying simulator.
It interprets the description of the attacks and produces an XML file, that will be used by the simulator.

### Attack Simulator
The attack simulator is the engine of the ASF++. It parses the XML file produced by the interpreter and 
simulates the effects of the attacks.

The attack simulator is based on Castalia/OMNeT++.


## Workflow
After deploying and building ASF++ on the local machine, it is easy to carry out an attack simulation:   
1. build a simulation scenario by using the NED language,
2. describe the effects of the attacks under survey by using the Attack Description Language,
3. interprets the attack description by using the Attack Description Interpreter,
4. launch the simulation.


## Build the simulator
After installing OMNeT++ 4.6, in the asfpp' directory type:

``` sh
$ ./makemake
$ make
```


## Acknowledgments
+ Francesco Racciatti  	<racciatti.francesco@gmail.com>
+ Marco Tiloca			<marco.tiloca84@gmail.com>
+ Alessandro Pischedda	<alessandro.pischedda@gmail.com>

