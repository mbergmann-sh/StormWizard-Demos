# StormWizard-Demos
Amiga code! This Repo contains some Demos on how to write code for using Amiga wizard.library with the code generated by StormWizard GUI builder in C. In order to build them, you will need at least:
- Amiga or Emulator running Workbench 3.1, 3.1.4 or 3.9
- StormWizard GUI builder, wizard.library and include files. You can get them here: http://stormwizard.amiforce.de/Download/stormwizard_2.3.lha
- a decent C compiler with AmigaOS 3.9 NDK installed - SAS/C, vbcc, StormC3, StormC4 or gcc v2.95 suggested. You can get the NDK here: https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&ved=2ahUKEwjMt_erz6ffAhWJGuwKHfJjAFEQFjAAegQIBxAB&url=http%3A%2F%2Fwww.haage-partner.de%2Fdownload%2FAmigaOS%2FNDK39.lha&usg=AOvVaw1lW3bgBPVzO4NCgRnREGjF

# Cave at
This code might contain some bugs, though having been tested and found working! Programs use german language for their GUI and code documentation - there are no translations available yet.

Be aware that the C include files for wizard.library in Bernd Roesch's downloadable archive on amiforce.de contain some non-amiga extra tokens that you'll have to remove by hand if not using a cross compiler!

# LICENSE
Copyright (C) 1987 - 2017 by Michael Bergmann. Placed in the public domain with some restrictions!

These files are part of my Amiga C coding series.

You may use or enhance this piece of software anyway you want to - as long as you don't violate laws or copyright issues. I hereby explicitely prohibit the usage of my work to people who believe in racism, fascism and any kind of attitude against democratic lifestyle. It is self-explanatory that this prohibits the usage of my work to any member or fan of the german AfD party.


This program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

# Compiling
...should be done on a real or emulated classic Amiga. You might also use some Amiga Cross Compiler toolchain on a PC or Mac. Be aware that you have to place the neccessary linker libs and include files into the right places by hand!

# Free Amiga native C compiler downloads
- VBCC: http://sun.hasenbraten.de/vbcc/index.php?view=main
- GCC v2.95 (ADE toolchain, native Amiga): https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=4&cad=rja&uact=8&ved=2ahUKEwja1avZ1affAhVQ-aQKHSEKBW4QFjADegQIBhAB&url=http%3A%2F%2Faminet.net%2Fpackage%2Fdev%2Fgcc%2FADE-repack&usg=AOvVaw0mlfZyBJAIEuq5RCBZMQJ7

# Free Amiga C cross compiler downloads
- GCC v2.95: https://github.com/cahirwpz/demoscene-toolchain
- VBCC and a more recent GCC version: https://github.com/bebbo/amiga-gcc (recommended)
