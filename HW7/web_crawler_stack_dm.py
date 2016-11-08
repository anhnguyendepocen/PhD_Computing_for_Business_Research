# -*- coding: utf-8 -*-
"""
web_crawler_stack.py
    - The web crawler with a stack.

@author: Dongwook Shin and Yash Kanoria, 2014/08/14
         Updated to use requests package by Dan Mechanic 2016/11/04

This web crawler walks through the URLs in the source website and keep 
crawling until there is no URL to be scanned. It stops crawling if a preset 
maximum number of urls have been visited.

"""
from bs4 import BeautifulSoup
import requests

url = "http://en.wikipedia.org/wiki/Logistic_regression"
urls = [url]    #queue of urls to crawl
seen = [url] # stack of urls seen so far
opened = []
nUrl = 0;
maxNumUrl = 10;

while len(urls) > 0 and nUrl < maxNumUrl:
    # DEQUEUE A URL FROM urls AND TRY TO OPEN AND READ IT
    try:
        curr_url=urls.pop(0)
        print("num. of URLs in stack: %d " % len(urls))
        #htmltext=urllib.request.urlopen(curr_url).readall().decode()
        htmltext = requests.get(curr_url).text
        opened.append(curr_url)
        nUrl += 1
    except Exception as ex: #if urlopen() fails
        print(ex)
        continue    #skip code below

    # IF URL OPENS, CHECK WHICH URLS THE PAGE CONTAINS
    # ADD THE URLS FOUND TO THE QUEUE url AND seen
    soup = BeautifulSoup(htmltext,"html.parser")  #creates object soup
    # Put child URLs into the stack
    for tag in soup.find_all('a', href = True): #find tags with links
        childUrl = tag['href']          #extract just the link
        childUrl = requests.compat.urljoin(url, childUrl)
        if url in childUrl and childUrl not in seen:
            urls.append(childUrl)
            seen.append(childUrl)

print("num. of URLs seen = %d, and scanned = %d" % (len(seen), nUrl))
print(opened)
