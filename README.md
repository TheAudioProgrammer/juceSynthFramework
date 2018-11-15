# juceSynthFramework
This is a clone/update of [theaudioprogrammer/juceSynthFramework](https://github.com/theaudioprogrammer/juceSynthFramework) with the following key changes:
* expanded *.gitignore* suitable for Mac+Windows builds
* fix *.jucer* file references to [micknoise/Maximilian](https://github.com/micknoise/Maximilian) (see below)
* added Visual Studio 2017 target to *.jucer* file, to allow building on Windows
* fixed a type-specification problem which interfered with Windows builds
* updated the [AudioProcessorValueTreeState](https://docs.juce.com/master/classAudioProcessorValueTreeState.html) initialization for compatibility with JUCE 5.4. (The original code used a deprecated form of the contstructor, resulting in a crash on startup, at least on the Windows platform.)
* added pitch-bend handling in *SynthVoice.h*

Before attempting to build this code, you should clone the [micknoise/Maximilian](https://github.com/micknoise/Maximilian) repo, ensuring that the *Maximilian* folder and the *juceSynthFramework* folder are *siblings* (live in the same parent folder). The updated references to Maximilian files are based on this assumption.

**Use only the tutorials branch.** I have not updated the others.
