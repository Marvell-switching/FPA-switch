# FPA-switch

The Forwarding Plane Abstraction (FPA) is an API library for configuring the Marvell® Prestera devices. 
The FPA represents a logical switch data plane model based on ONF switch data plane abstraction model, and is used to enable OpenFlow, SAI/SONiC to run on top of Prestera devices.

The FPA provides API calls to support configuring, updating and interrogating Prestera devices tables 
for certain capabilities. These capabilities can include supported match fields, actions, instructions, 
and more. They can also include status properties, such as current resource usage.
The FPA model proves to be an efficient and modular programming approach API library.

Usage:
    git clone https://github.com/Marvell-switching/FPA-switch.git
    Libraries in bin/intel/lib
   
    To build debian package:
        cd FPA-switch
        make
	Resulting package resides in bin/intel

