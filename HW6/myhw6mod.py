#!/usr/bin/env python

def hwfunone(n):
	for i in range(1,n+1):
		for j in range (1,n+1):
			print(i,"+",j,"=",(i+j))
	return()


def haversine(lon1,lat1,lon2,lat2):
	from math import radians, cos, sin, asin, sqrt
	"""
	Calculate the great circle distance between two points
	on the earth (specified in decimal degrees)
	"""
	# convert decimal degrees to radians
	lon1, lat1, lon2, lat2 = map(radians, [abs(lon1), abs(lat1), abs(lon2), abs(lat2)])
	# haversine formula
	dlon = lon2 - lon1
	dlat = lat2 - lat1
	a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
	c = 2 * asin(sqrt(a))
	#r = 6371 # Radius of earth in kilometers. Use 3956 for miles
	r = 3956 # Radius of earth in miles
	distance = c * r
	return(distance)

