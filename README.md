Summary
=======
Repository with an extremely simple driver to read information from 
the Polhemus (in cm for tracker position and quaternion for rotation)

Installation instructions
==========================
These have been successfully tried in a Ubuntu 14.04 system, 32-bits and a Debian Jessie, 64 bits.

Steps
------
1. Install fxload

2. Install Linux driver for Polhemus (piterm):

   ftp://ftp.polhemus.com/pub/Linux_tools/

3. Install rules file (VERY IMPORTANT)
   ```
   cd Software/piterm-1.0.4/fw.rules/
   sudo cp 90-Polhemus_trkr.rules /etc/udev/rules.d/
   ```

   Example: 
   Before rules: Bus 001 Device 003: ID 0f44:ff21 Polhemus

   After rules: Bus 002 Device 005: ID 0f44:ff20 Polhemus

4. Reload rules.d (probably you should pull out and in again the Polhemus for this to take effect as well
   
   ```
   sudo udevadm control --reload-rules
   sudo mount --bind /dev/bus /proc/bus
   sudo ln -s /sys/kernel/debug/usb/devices /proc/bus/usb/devices
   ```


5. Load library firmware
   * First get the path to device
     PATH = sudo ./getdevpath.sh -v 0f44 -p ff20
     PATH= /proc/bus/usb/001/004

   * Go to /usr/local/share/PolhemusUsb and load firmware
     ```
     sudo /sbin/./fxload -t fx2lp -D /proc/bus/usb/001/004 -I LbtyUsbHS.hex -s a3load.hex 
     ```
Note
----
 I noticed that once you load the firmware, the path is not important
(I reloaded the Liberty and got a different path and it was still working - even without calling fxload again)

Usage
=====
The main executables you will want to use are the driver and the reader itself:

trackerd.cpp
-------------
Daemon to constantly read and output the state of the Polhemus:

```
trackerd -s 1 -t 0 -c liberty-chan
```

where s denotes the type of communication (1 is usb, 0 is serial). t indicates the type of tracker device
(in our case a HS Liberty) and c is the name of the channel that outputs the state of the markers.


