Simplified CC3000 library
-------------------------
This is a try at getting the CC3000 working with a uC setup that is as simple
as possible, while containg the TI code in a clean way. In particular, the
code here reduces the complexity of adapting the TI library to a certain
microcontroller to the following, minimal set of functionality, trading
simplicity for efficiency and performance:

- general purpose GPIO pins connected to SPI_CS, SPI_MISO, SPI_MOSI, SPI_SCLK,
  SPI_IRQ and VBAT_EN_SW, using **SOFTWARE SPI only**. This is an adaptation
  of the ArduinoCC300 software SPI code, from
  https://github.com/cmagagna/ArduinoCC3000.git.

- the SPI IRQ pin is polled, so only one generic regular 'systick' interrupt
  is needed. **No additional external interrupts**.

- the code is in a nicely contained library directory structure, and all that
  is needed to compile is (assume being in root directory of checkout):
    
   $ cd src; CC=&lt;insert-your-cross-compiler-here&gt; make

Additionaly a couple of odd behaviors have been observed with the sample chip(s)
that I got into my hands, for which there have been workarounds/fixes
implemented. This chip (firmware rev. 1.10) apparently needed the
following fixes:

- extra delays were necessary during SPI send

- Calling the socket API send(..) function waits for a response from the CC3K,
  but there does not seem to be any answer. This might be fixed with newer
  firmwares(?)

- a bunch of errors that appear when linking against newlib (in the case of an
  ARM uC) have been fixed

This configuration has been tested so far to work on a bare CC3K, wired
'deadbug style' to an STM32F0DISCOVERY board. It works from an internal clock
of 8MHz up to the full 48MHz (RC oscillator 'HSI'). For a simple 'TCP echo
server' based on this library fork, look at

https://github.com/onnokort/stm32f0-cc3000-echotest


How to use and how to port
--------------------------
To compile the library, just select your cross compiler as described above and
run make. The Makefile is as easy as it can get. To link with your custom
project, add to your compilation command line(s):

 -I&lt;path-to-cc3000-library&gt;/include/

Then use the library by including like this:

    #include <cc3000/some-include.h>

To the line used for linking, the following needs to be added:

 -L&lt;path-to-cc3000-library&gt;/src/

That's it for the build process. All functionality relies on a bunch of
functions that should be easy to fill in. All necessary prototypes for these
functions and documentation on how to implement them can be found in the file

  &lt;path-to-cc3000-library&gt;/include/cc3000/hardware.h

The functions that need to be filled in all follow the pattern of
cc3k_*. Filling in cc3k_global_irq_enable(..) is optional.

Reference files
---------------
This is (so far) an adaptation of version V1.11 of the TI library,
'swrc277.zip', with MD5 a6c5b8bf2c62321a6d7bae35faf76ced.


Feedback
--------
If you use this modified library, I appreciate questions & feedback to
Onno Kortmann <onno@gmx.net>.

