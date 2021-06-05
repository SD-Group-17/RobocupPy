To use doxygen to generate documentation either copy the doxygen-config file to the folder you want documented or generate a new config file in that folder using the command:
`doxygen -g <name-of-config-file>`
Note: doxygen must be installed on your system
    Ubuntu:
    `sudo apt install doxygen`

To run doxygen:
`doxygen <name-of-config-file>`

Output is in html or LaTex form -- open html in browser.

NOTE: doxygen config file should be moved to path in which the files you want to document are contained.