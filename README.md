# Denial-of-Service
A simple implementation of a DoS attack

## Usage
To compile te program, simply run ```make``` in the root directory of project. This will create a directory called ```build```
with the binary.

To run the program, execute ```build/denial.bin```.

### Parameters
The script program accepts some arguments:
```
./denial.bin [OPTION...] DOMAIN/IP  

-p | --port : Set the port for the attack. Default is port 21.
-v | --verbose : Set operation mode to verbose
-c | --connections: Set how many connections the program will attempt in target
-V | --version : Display the version and useful information
```
Example:
```./denial.bin -c 10000  <url> --port 22 --verbose```: The program will attempt to open ```10.000``` connections in port 
```22``` at ```<url>```, outputing more information because of ```--verbose```

### Setting up
Run ```install.sh``` script. It will compile and put the binary in ```/usr/local/bin/```. Reload your terminal session
to be able to use the program directly.

## License
This code is under GPLv3 License, see ```LICENSE``` for more information.

## Notes
This is a very simple DoS implementation, all connections are oppened from the same IP address.
