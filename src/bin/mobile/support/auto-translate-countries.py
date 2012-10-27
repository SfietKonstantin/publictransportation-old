#!/usr/bin/python
# -*- coding: utf-8 -*-

import argparse
import urllib
import urllib2
import codecs
import sys
import re

# Fetch a country using wikipedia page
def fetchCountry(country, lang, dataRegExp, purgedDataRegExp):
    print "-----------"
    print "Fetching " + country

    if country in replacementList:
        print "Replacing " + country + " with " + replacementList[country]
        country = replacementList[country]

    try:
        url = "http://en.wikipedia.org/w/api.php?action=query&titles=" + urllib.quote_plus(country)
        url += "&prop=langlinks&format=xml&lllimit=500&lllang=" + lang
        response = urllib2.urlopen(url)
        data = response.read()
        dataResult = dataRegExp.search(data)
        if dataResult != None:
            # Post proces

            country = dataResult.group(1)
            purgedDataResult = purgedDataRegExp.search(country)
            if purgedDataResult != None:
                purgedData = purgedDataResult.group(1)
                country = country.replace(purgedData, "")
            else:
                country = country.replace("<", "")
            print country
            return unicode(country, "utf-8")
        else:
            print "Error processing " + country
            print data
            return None
    except Exception:
        print "Other error"


    return None

# Main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=
"""publictransportation support tool used to perform countries translation

This tool perform translation of countries using wikipedia.""")
    parser.add_argument('translationfile', metavar='translationfile', type=str,
                        help="""Translation file""")
    parser.add_argument('countriesfile', metavar='countriesfile', type=str,
                        help="""Countries file""")
    parser.add_argument('lang', metavar='lang', type=str,
                        help="""Wikipedia language (Wikipedia website prefix)""")
    parser.add_argument('outputfile', metavar='outputfile', type=str,
                        help="""Output translation file""")
    args = parser.parse_args()

    translationfile = args.translationfile
    countriesfile = args.countriesfile
    lang = args.lang
    outputfile = args.outputfile

    # Replacement list for countries that wikipedia fail to recognize
    replacementList = {"Bahamas": "The Bahamas", "Brunei Darussalam": "Brunei",
    "Congo, The Democratic Republic of The": "Democratic Republic of the Congo",
    "Falkland Islands (Malvinas)": "Falkland Islands",
    "French Southern Territories": "French Southern and Antarctic Lands",
    "Gambia": "The Gambia", "Heard Island and Mcdonald Islands": "Heard Island and McDonald Islands",
    "Holy See (Vatican City State)": "Vatican City", "Iran, Islamic Republic of": "Iran",
    "Korea, Republic of": "South Korea", "Libyan Arab Jamahiriya": "Libya",
    "Macao": "Macau", "Macedonia, The Former Yugoslav Republic of": "Republic of Macedonia",
    "Micronesia, Federated States of": "Federated States of Micronesia",
    "Moldova, Republic of": "Moldova", "Myanmar": "Burma",
    "Pitcairn": "Pitcairn Islands", "Reunion": u"Réunion", "Russian Federation": "Russia",
    "Saint Vincent and The Grenadines": "Saint Vincent and the Grenadines",
    "Sao Tome and Principe": u"São Tomé and Príncipe",
    "South Georgia and The South Sandwich Islands": "South Georgia and the South Sandwich Islands",
    "Syrian Arab Republic": "Syria", "Taiwan, Province of China": "Taiwan",
    "Tanzania, United Republic of": "Tanzania", "Timor-leste": "East Timor",
    "Viet Nam": "Vietnam", "Virgin Islands, British": "British Virgin Islands",
    "Virgin Islands, U.S.": "United States Virgin Islands"}


    # Load countries
    countries = []

    try:
        f = codecs.open(countriesfile, 'r', "utf-8")
    except IOError :
        print "Error: could not open countries file"
        sys.exit(0)
    for line in f:
        splittedLine = line.strip().split(":")
        countries.append(splittedLine[1])
    f.close()

    # Parse the translation file
    try:
        f = codecs.open(translationfile, 'r', "utf-8")
    except IOError :
        print "Error: could not open translation file"
        sys.exit(0)

    try:
        out = codecs.open(outputfile, 'w', "utf-8")
    except IOError :
        print "Error: could not open output file"
        sys.exit(0)

    # Prepare regexp
    sourceRegExp = re.compile("<source>([^<]*)</source>")
    unfinishedTranslationRegExp = re.compile("<translation type=\"unfinished\"/?>(([^<]*)</translation>)?")
    dataRegExp = re.compile("xml:space=\"preserve\">([^<]*<)/ll>")
    purgedDataRegExp = re.compile("(\([^\)]*\)<)")

    correctFile = False
    currentCountry = None
    for line in f:
        if "<!DOCTYPE TS>" in line:
            correctFile = True
        if correctFile:
            sourceResult = sourceRegExp.search(line)
            unfinishedTranslationResult = unfinishedTranslationRegExp.search(line)
            if sourceResult != None:
                country = sourceResult.group(1)
                if country in countries:
                    currentCountry = country
                out.write(line)
            elif unfinishedTranslationResult != None:
                if currentCountry != None:
                    fetchedCountry = fetchCountry(currentCountry, lang, dataRegExp, purgedDataRegExp)
                    if fetchedCountry != None:
                        out.write(u"        <translation>" + fetchedCountry + u"</translation>\n")
                    else:
                        out.write("        <translation type=\"unfinished\"></translation>\n")
                else:
                    out.write(line)
            elif "</message>" in line:
                currentCountry = None
                out.write(line)
            else:
                out.write(line)
        else:
            out.write(line)

