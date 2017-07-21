# Light-Show-Toolkit

This software can be used to play "Light Show" Files, which are files designed to go along with a light system (Such as Hue or Milight) and play a timed lightshow with music!

## Currently Supports: 
###Currently Supported Light-Systems: 
* Milight

### Currently supported File-Formats for light-shows
* .LS (Lightshow file format)
### Currently supported Operating systems
* Windows

### Currently support audio file formats
* Windows: 
** .Wav

## LightShow file format
The lightshow file format is a unique file format used by this program, "Example.ls" outlines the syntax and functionality of the format


## Available "Commands"
* ColourChange: Change the colour to what is specified for the currently selected groups
* Wait: Pause for an amount of seconds
* Group: Set the current group 
* FunctionName: Play the function
* FunctionPointer: Not implemented yet
* SpecificCommand: Not implemented yet
  
## Available Operations
Operations can be applied to a command, changing their functionality

Within the LS file format, a command preceeded by '+' denotes "add", '-' denotes "Subtract", nothing denotes "Set"

### Set Operator (Default)
* For Colour, will SET the colour to the given value for each "Currently Selected Group" 
* For Group, will SET the "Currently Selected Group" to the given value
* For FunctionName, will run every function
    
### Add operator (+Command)
* For Colour, will ADD the colour to each light individually
* For Group, will ADD the group to the currently selected group
* For FunctionName, will run every command with the + operator
### Subtract Operator (-Command)
* The opposite for each

### Repeat Operator (Integer)
* For any command, will execute that number of times

## General Principle of changing a light's colour:

To change the colour of a light, 
1. FIRST you set the "Current Groups" to the light.
2. Secondly you fire off a Colour. 

## Settings Files

### Milight Settings
MiLightSettings.txt holds the settings for MiLight. 
* The first line is the IP Address (e.g: 10.0.0.65)
* The second line is the PORT (e.g: 8899)
* The third line is UDP or TCP (Protocol to use)
