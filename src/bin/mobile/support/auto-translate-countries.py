#!/usr/bin/python
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

