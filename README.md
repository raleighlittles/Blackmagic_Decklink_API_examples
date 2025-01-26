# About

This repository contains an example of how to build an application that uses the Blackmagic Decklink SDK.

https://www.blackmagicdesign.com/developer/products/capture-and-playback/sdk-and-software

The code builds a simple binary that lets you view basic status information about your Decklink - written for PCIe devices.

It uses CMake to build (the example code provided by Blackmagic uses only Makefiles), and modern C++ features.

Here's what you'll get when you run it:

```
DeckLink Mini Recorder 4K
API version: 14.4
Device Temperature: 60 °C
PCIe info: 2 Gb/s (4 lanes)
Could not get video display mode. Are you sure a video input is connected?
Device ID: 559022103
```

# Usage/Build

```bash
$ cmake -S . -B build
$ cmake --build build
```

Then run the executable:

```bash
$ ./decklinkInfo
```

# Roadmap

- [ ] Add cross-compilation support to be able to build Windows executables on Linux