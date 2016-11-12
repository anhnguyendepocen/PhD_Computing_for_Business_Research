# -*- coding: utf-8 -*-
"""
Computings for Business Research, B9122 Fall 2016
Homework #7

Instructor Dan Mechanic

Complete this web crawler:

This web crawler walks through the URLs in the source website. It only crawls 
child URLs if it contains at least one of the pre-defined key words. Each URL
has a score, which is defined as the number of occurrence of the key words 
in the HTML body. 

As an output it prints out the sorted list of URLs based on the score.

"""

import requests
import re
from bs4 import BeautifulSoup as bs

def html_words(soup):
    # A function that takes BeautifulSoup object as an input 
    # and converts the text body into a list of words.

    # a regular expression to remove non-alphanumeric characters
    regex = re.compile('[^a-zA-Z]') 

    text = soup.get_text()
    text = text.lower()
    text = regex.sub(' ', text)
    words = text.split()
    
    return words


url = "http://www8.gsb.columbia.edu/"        
maxNumUrl = 50      # the maximum number of URLs to be scanned
keywords = ['finance', 'engineering', 'business', 'research']

# initialize data arrays to be used
"""
    Hint: you may assign an arbitrary value to the parent score of
    "http://www8.gsb.columbia.edu/", which doesn't have a parent. It will
    be the first url opened in any case. 
    You will maintain a datastructure "urls" for unopened urls, another 
    one "opened" for opened urls, and possibly a third one "seen" that you 
    use to avoid repetition.
        
    insert your code
"""
urls = [url]
seen = [] # stack of urls seen so far
unopened = {}
opened = {}


while len(urls) > 0 and len(seen) < maxNumUrl:
    # pick an URL with the highest parent score,
    # open the URL, and get htmltext from it

    try:
        curr_url=urls.pop(-1)
        seen.append(curr_url)
        print("num. of URLs in stack: %d " % len(urls))
        htmltext = requests.get(curr_url).text
    except Exception as ex: #if urlopen() fails
        print(ex)
        continue    #skip code below


    # convert htmltext into a list of words
    soup = bs(htmltext, "html.parser")
    # words = html_words(soup)
    words_for_scoring = html_words(soup)
    # get score of the URL, and
    occurrence_for_scoring = 0
    for w in words_for_scoring:
        if w in keywords:
            occurrence_for_scoring += 1
    opened[curr_url] = occurrence_for_scoring
        
    # put child URLs into "urls", only if the score > 0
    if occurrence_for_scoring != 0:
        for tag in soup.find_all('a', href = True): #find tags with links
            childUrl = tag['href']          #extract just the link
            childUrl = requests.compat.urljoin(url, childUrl)
            if childUrl not in seen:
                    urls.append(childUrl)
                    unopened[childUrl] = occurrence_for_scoring
                
# print top 10 list of URLs with the highest scores
top = sorted(opened.items(), key = lambda x: x [1], reverse = True)  # sort by occurrence
print(top[:10])
