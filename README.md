![CI build badge](https://https://github.com/raleighlittles/Blackmagic_Decklink_API_examples/actions/workflows/main.yml/badge.svg)

# About

This repository contains an example of how to build an application that uses the Blackmagic Decklink SDK.

https://www.blackmagicdesign.com/developer/products/capture-and-playback/sdk-and-software

The code builds a simple binary that lets you view basic status information about your Decklink - written for PCIe devices.

It uses CMake to build (the example code provided by Blackmagic uses only Makefiles), and modern C++ features.

Here's an example of what you'll see when you run the tool:

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


<a href="https://www.buymeacoffee.com/raleighlittles" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="50" width="200"></a>