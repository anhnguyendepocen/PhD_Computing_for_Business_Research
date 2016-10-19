#!/usr/bin/env python

import myhw6mod as mymod
from sys import argv

if len(argv) != 2:
	print("You must enter one integer argument.")
else:
	user_input = argv[1]	
	check = 0
	while(check!=1):
	    try:
	    	x = int(user_input)
	    except:
	    	print("You must enter one integer argument.")
	     	user_input = input("Please enter a valid input.")
	    else:
	    	check = 1
	    	break

	mymod.hwfunone(x)


# used to run but now doesn't work
# should we give the user another chance if the length is not 2?