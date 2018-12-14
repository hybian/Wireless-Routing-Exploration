# CPRE543-Project

By: Hongyi Bian and Omar Taylor

## Getting Started with Contiki-NG
The [getting started](http://www.contiki-os.org/start.html) page of Contiki-NG is incomplete nor are other online
resources for setting up so this section strives to be a getting started guide that doesn't make assumptions.

There are two methods of getting started with Contiki:
- Instant Contiki
  1. You will need VM client. Virtual Box or VMWare works. I opted for using VMware Workstation 15 since I've had issues 
  with hardware devices communicating with Virtual Box in the past.
  2. Download Instant Contiki from it's [hosting page](https://sourceforge.net/projects/contiki/files/Instant%20Contiki/).
  3. Unzip the file inside.
  4. Open the virtual machine from the unzipped folder from within your VM client. Password is "user".
  5. Open terminal.
  6. `cd /contiki/examples/hello-world` (This is our sanity test program)
  7. You'll need to following libraries, a number of which may not be pre-installed with Instant Contiki for some
  reason.
      - `sudo apt-get update`
      - If you're just working with Tmote Sky: `sudo apt-get install build-essential git binutils-msp430 gcc-msp430 
      msp430-libc msp430mcu mspdebug`
      - If you're working with the OpenMote add "gcc-arm-none-eabi gdb-arm-none-eabi" to the end of the previous code 
      block.
      - A Java runtime environment: `sudo apt-get install openjdk-8-jdk openjdk-8-jre ant libncurses5-dev`
      - Contiki OS is a 32-bit environment so in case you're running a 64-bit Linux OS (which Instant Contiki is as of 
      this writing): `sudo apt-get install lib32ncurses5`.
  8. <b>Compiling and running for the native platform:</b>
      1. `sudo make` (TARGET=native by default. Compiles code for native platform)
      2. `sudo ./hello-world.native` (runs compiled program)
      3. Should see something along the lines of: <br>
          > Contiki-2.6-2450-geaa8760 started with IPV6, RPL
          Rime started with address 1.2.3.4.5.6.7.8
          MAC nullmac RDC nullrdc NETWORK sicslowpan
          Tentative link-local IPv6 address fe80:0000:0000:0000:0302:0304:0506:0708
          Hello, world
      4. Ctrl+C to quit.
  9. **Compiling and running for \<platform\>** (we're using a Tmote Sky):
      1. Make sure your device is connected to the virtual machine or the following steps may fail (i.e. try running 
      `lsusb` to check if your device is connected)
      2. `sudo make TARGET=<platform> savetarget` (saves target compilation for future to save time. Optional. Replace
      "<platform>" with your platform. i.e. Tmote Sky would by "sky")
      3. `sudo make hello-world.upload` (Flashes code to platform)
      4. `sudo make login` (View output from platform. If you don't see the output, press the reset button on platform)
      5. Should see something along the lines of: <br>
          > Rime started with address 0.18.116.0.17.108.193.246
            MAC 00:12:74:00:11:6c:c1:f6 Contiki-3.x-3345-g32b5b17f6 started. Node id is set to 33.
            nullsec CSMA ContikiMAC, channel check rate 8 Hz, radio channel 26, CCA threshold -45
            Tentative link-local IPv6 address fe80:0000:0000:0000:0212:7400:116c:c1f6
            Starting 'Hello world process'
            Hello, world
      5. Ctrl+C to quit.
- Manual Contiki **Recommended**
  1. Download Ubuntu (This guide uses Ubuntu Desktop 18.04.1)
  2. Install onto a VM client (This guide uses VMware Workstation)
  3. Power on VM and open terminal.
  4. You'll need to following libraries:
      - `sudo apt-get update`
      - If you're just working with Tmote Sky: `sudo apt-get install build-essential git binutils-msp430 gcc-msp430 
        msp430-libc msp430mcu mspdebug`
      - If you're working with the OpenMote add "gcc-arm-none-eabi gdb-arm-none-eabi" to the end of the previous code 
        block.
      - A Java runtime environment: `sudo apt-get install openjdk-8-jdk openjdk-8-jre ant libncurses5-dev`
      - Contiki OS is a 32-bit environment so in case you're running a 64-bit Linux OS (which Instant Contiki is as of 
        this writing): `sudo apt-get install lib32ncurses5`.
      - Python2.7 (Ubuntu 18.04 comes with Python3 default): `sudo apt-get install python`
  5. Clone the Contiki-NG source code:
     - While in your folder of choice (this guide clones from home folder), run: 
     `git clone https://github.com/contiki-ng/contiki-ng`
  6. Follow from step viii in the Instant Contiki setup guide.

<br><br>
**Note from Omar:**
>  I've tried Instant Contiki and does a good job of being a quick way to get started, but the reason this method isn't 
my first choice is because it doesn't work out of the box even when following Contiki-NG's own getting started
instructions -- which doesn't quite make this method as instant as you'd like it to be. While I was able to resolve the
issues that made it not work for my purposes, I was concerned about running into issues later so I opted for building
Contiki manually so I know exactly what went into the set-up process. <br>**Update:** No longer recommending Manual Contiki. For some reason perhaps related to using Ubuntu 18.04, how msp430-gcc is configured, or something else, some example programs in contiki end up using all of the ROM space on the Tmote Sky platform. On Instant Contiki this doesn't happen and the programs we've tried can be successfully compiled and programmed onto the sky platform.
