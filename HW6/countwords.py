#!/usr/bin/env python

import sys

# read in the file
try: 
    if sys.argv[1] == "-":
        lines = sys.stdin.read()
    else:
        # use open() to open a file 
        lines = open(sys.argv[1]).read()
except:
    print("Usage: %s <filename|->" % sys.argv[0])
    sys.exit(1)

# create a dictionary to store words and their number of occurences
words_freq = {}

# fill in the dictionary
for word in lines.split():
	if word.lower() not in words_freq: 
		words_freq[word.lower()]=0
	words_freq[word.lower()] += 1

# sort the dictionary based on its values (word frequency)
sorted_dictionary = sorted(words_freq.items(), key= lambda x: x[1], reverse=True)

# print out the sorted dictionary line-by-line
for i,k in sorted_dictionary[:5]:
    print(k,i)

