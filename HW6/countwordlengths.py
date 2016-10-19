#!/usr/bin/env python

import sys

# read in the file
try: 
    if sys.argv[1] == "-":
        lines = sys.stdin.readlines()
    else:
        # use open() to open a file 
        lines = open(sys.argv[1]).readlines()
except:
    print("Usage: %s <filename|->" % sys.argv[0])
    sys.exit(1)

# create a dictionary to store words and their lengths
words_lengths = {}
        
# fill in the dictionary
for line in lines:
	for i in line.split():
		words_lengths[i]=len(i)


# sort the dictionary based on its values (word lengths)
sorted_dictionary = sorted(words_lengths.items(), key= lambda x: x[1], reverse=True)
print(sorted_dictionary[:10])




# read from a list, is for line in lines ok then? right now repetition messes things up?
# where is the dict/words file?