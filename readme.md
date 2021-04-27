# Algorithms and Data Structures Coursework (SET08122)
A Command Line Implementation of Milton Bradley's Connect Four Board Game for SET08122's Coursework

[![Releases](https://img.shields.io/github/release/lewiswatson55/ADS_Connect-Four/all.svg?style=flat-square)](https://github.com/lewiswatson55/ADS_Connect-Four/releases)

## Dependencies
[Visual Studio Developer Command Prompt](https://docs.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell)
<br>
Other compilers may work however, this project has only been tested using NMAKE on the Visual Studio Dev Command Prompt

# Usage
To start the program double click on the ADS_Coursework_40432878 executable or run it in a command prompt.

```
$ ADS_Coursework_40432878.exe
```

# Set Up
Note 0: The GCC Compiler is not recommended as there have been issues found using it before.

## Compiling the executable:
1. Open Visual Studio's Developer Command Prompt

2. Compile 'all' using NMAKE: (this will also remove old builds from the folder via nmake clean) ``` nmake all ```

or

2. Manually compile using CL ``` cl /o ADS_Coursework_40432878 main.c games.c ```

That's your setup done.


# Author and Acknowledgements

Created by: [Lewis N Watson](https://github.com/lewiswatson55/)
