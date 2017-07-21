# Light-Show-Toolkit

This software can be used to play "Light Show" Files, which are files designed to go along with a light system (Such as Hue or Milight) and play a timed lightshow with music!

Currently Supported Light-Systems: 
  -Milight

Currently supported File-Formats
  -.LS (Lightshow file format)
  
## LightShow file-format
The lightshow file format is a unique file format used by this program, "Example.ls" outlines the syntax and functionality of the format


## Available "Commands"
    -ColourChange: Change the colour to what is specified for the currently selected groups
    -Wait: Pause for an amount of seconds
    -Group: Set the current group 
    -FunctionName: Play the function
    -FunctionPointer: Not implemented yet
    -SpecificCommand: Not implemented yet
  
## Available Operations
>Operations can be applied to a command, changing their functionality

>Within the LS file format, a command preceeded by '+' denotes "add", '-' denotes "Subtract", nothing denotes "Set"

### Set Operator (Default)
    -For Colour, will SET the colour to the given value for each "Currently Selected Group" 
    -For Group, will SET the "Currently Selected Group" to the given value
    -For FunctionName, will run every function
    
### Add operator
    -For Colour, will ADD the colour to each light individually
    -For Group, will ADD the group to the currently selected group
    -For FunctionName, will run every command with the + operator
### Subtract Operator
    -The opposite for each

## General Principle of changing a light's colour:

To change the colour of a light, 
  FIRST you set the "Current Groups" to the light.
  Secondly you fire off a Colour. 
 
