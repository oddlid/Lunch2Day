#!/usr/bin/python2.7
# -*- coding: utf-8 -*-
from BeautifulSoup import BeautifulSoup
import urllib2

class ScraperMimolett():

    def get_text(self):
        url = "http://www.mimolett.se/dagens-lunch/"
        content = urllib2.urlopen(url).read()
        soup = BeautifulSoup(content)
        div = soup.find('div', attrs={'class': 'entry'})
        for e in div.findAll('br'):
            e.replaceWith('newline')
        text = []
        paras = [x for x in div.findAllNext('p')]
        for p in paras:
            line = p.text
            line = line.strip()
            for l in line.split('newline'):
                text.append(l)
	return text

    def get_todays_dishes(self, text, day='Fredag'):
	#There are always two dishes at mimolett
        for index, elem in enumerate(text):
            if elem == day:
		dishes = text[index+1:index+3]
		return dishes

    def get_pasta(self, text):
        for index, elem in enumerate(text):
            if 'VALFRI DAGENS PASTAR' in elem:
		pasta_dishes = text[index+1:]
                return pasta_dishes

    def get_dishes(self):
    	dishes = []
	text = self.get_text()
    	todays_dishes = scraper.get_todays_dishes(text)
    	pasta_dishes = scraper.get_pasta(text)
	dishes.extend(todays_dishes)
	dishes.extend(pasta_dishes)
	return dishes

class Dishes():

    def __init__(self):
	self.dishes = None

    def dump(self):
        for dish in self.dishes :
            print dish

    def set(self, dishes):
	self.dishes = dishes 


if __name__ == "__main__":
    scraper = ScraperMimolett()
    mimolett_dishes = scraper.get_dishes()
    
    dishes = Dishes()
    dishes.set(mimolett_dishes)
    dishes.dump()	
