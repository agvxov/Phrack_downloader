#!/bin/python3
from bs4 import *

fileNameTemplate = "PHRACK_issue_"

for i in range(68):
	# Read
	f = open(fileNameTemplate + str(i + 1), "r")
	text = f.read()
	f.close()
	# Sanatize
	soup = BeautifulSoup(text, 'html.parser')
	text = soup.get_text()
	# Write
	f = open("B/" + fileNameTemplate + str(i + 1) + ".txt", "w")
	f.write(text)
	f.close()
