#########################################################################
# File Name: bibconvert.py
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Fri Dec  9 12:00:28 2016
#########################################################################
#!/bin/python

import sys
import re
import datetime
import bibtexparser 

def read(filenames, commentPrefix):
    # read content from bibtex files 
    content = ""
    for filename in filenames:
        with open(filename) as inFile:
            for line in inFile:
                # remove comments 
                # it is not perfect now, since I cannot merge them 
                line = re.sub(re.compile("[ \t]"+commentPrefix+".*?$"), "", line)
                line = re.sub(re.compile("^"+commentPrefix+".*?$"), "", line)
                content = content+line+"\n"

    bibDB = bibtexparser.loads(content)
    return bibDB

def getDatetime(entry):
    date = entry['year']
    timeFormat = "%Y"
    if 'month' in entry and entry['month']:
        date = date+","+entry['month']
        timeFormat = "%Y,%B"
        if 'day' in entry and entry['day']:
            date = date+","+entry['day'].split('-', 1)[0]
            timeFormat = "%Y,%B,%d"
    return datetime.datetime.strptime(date, timeFormat)

def getAddressAndDate(entry):
    addressAndDate = ""
    prefix = ""
    if 'address' in entry and entry['address']:
        addressAndDate += prefix + entry['address']
        prefix = ", "
    if 'month' in entry and entry['month']:
        addressAndDate += prefix + datetime.datetime.strptime(entry['month'], "%B").strftime("%b")
        prefix = " " if 'day' in entry and entry['day'] else ", "
    if 'day' in entry and entry['day']:
        addressAndDate += prefix + entry['day'].replace("--", "-")
        prefix = ", "
    if 'year' in entry and entry['year']:
        addressAndDate += prefix + entry['year']
    return addressAndDate

def printBibDB(bibDB, highlightAuthors, suffix):
    # differentiate journal and conference 
    # I assume journal uses 'journal' 
    # conference uses 'booktitle'
    journalEntries = []
    conferenceEntries = []

    for entry in bibDB.entries:
        if 'journal' in entry:
            journalEntries.append(entry)
        else:
            conferenceEntries.append(entry)
    # sort by years from large to small 
    journalEntries.sort(key=lambda entry: getDatetime(entry), reverse=True)
    conferenceEntries.sort(key=lambda entry: getDatetime(entry), reverse=True)
    stringMap = dict(bibDB.strings)

    # call kernel print functions 
    if suffix.lower() == 'web':
        print """
# jemdoc: menu{MENU}{publications.html}
# jemdoc: addcss{yibolin_homepage/jemdoc.css}
# jemdoc: title{Yibo Lin's Homepage}

= Publications

"""
        printWeb(bibDB, stringMap, highlightAuthors, journalEntries, 'journal', 'journal')
        printWeb(bibDB, stringMap, highlightAuthors, conferenceEntries, 'conference', 'booktitle')
    elif suffix.lower() == 'cv':
        print """
\\begin{rSection}{Publications}

"""
        printCV(bibDB, stringMap, highlightAuthors, journalEntries, 'journal', 'journal')
        printCV(bibDB, stringMap, highlightAuthors, conferenceEntries, 'conference', 'booktitle')
        print """
\end{rSection}

"""
    else:
        assert 0, "unknown suffix = %s" % suffix

def printWeb(bibDB, stringMap, highlightAuthors, entries, publishType, booktitleKey):
    prefix = ""
    if publishType == 'journal':
        print "=== Journal Papers\n"
        prefix = "J"
    else:
        print "=== Conference Papers\n"
        prefix = "C"
    # print 
    currentYear = '' 
    count = len(entries)
    for i, entry in enumerate(entries):
        if not currentYear or currentYear.lower() != entry['year'].lower():
            currentYear = entry['year']
            print "==== %s\n" % (currentYear)
        author = entry['author']
        if highlightAuthors: # highlight some authors 
            for highlightAuthor in highlightAuthors:
                author = author.replace(highlightAuthor, "*"+highlightAuthor+"*")
        title = entry['title'].replace("{", "").replace("}", "")
        booktitle = stringMap[entry[booktitleKey]] if entry[booktitleKey] in stringMap else entry[booktitleKey]
        address = entry['address'] if 'address' in entry else ""
        publishlink = entry['publishlink'] if 'publishlink' in entry else ""
        annotate = entry['annotateweb'] if 'annotateweb' in entry else ""
        if publishlink: # create link if publishlink is set 
            title = "[" + publishlink + " " + title +"]"
        addressAndDate = getAddressAndDate(entry)
        print """
- \[%s%d\] %s, 
  "%s", 
  %s, %s. 
  %s
        """ % (prefix, count, author, title, booktitle, addressAndDate, annotate)
        count = count-1

def printCV(bibDB, stringMap, highlightAuthors, entries, publishType, booktitleKey):
    prefix = ""
    if publishType == 'journal':
        print """
\\textbf{Journal Papers}
        """
        prefix = "J"
    else:
        print """
\\textbf{Conference Papers}
        """
        prefix = "C"
    print """
\\begin{description}[font=\\normalfont]
%{{{
    """

    # print 
    currentYear = '' 
    count = len(entries)
    for i, entry in enumerate(entries):
        if not currentYear or currentYear.lower() != entry['year'].lower():
            currentYear = entry['year']
        author = entry['author']
        if highlightAuthors: # highlight some authors 
            for highlightAuthor in highlightAuthors:
                author = author.replace(highlightAuthor, "\\textbf{"+highlightAuthor+"}")
        title = entry['title']
        booktitle = stringMap[entry[booktitleKey]] if entry[booktitleKey] in stringMap else entry[booktitleKey]
        publishlink = entry['publishlink'] if 'publishlink' in entry else ""
        annotate = entry['annotatecv'] if 'annotatecv' in entry else ""
        if publishlink: # create link if publishlink is set 
            title = "\\href{" + publishlink + "}{" + title +"}"
        addressAndDate = getAddressAndDate(entry)
        print """
\item[{[%s%d]}]{
        %s, 
    ``%s'', 
    %s, %s.
    %s
}
        """ % (prefix, count, author, title, booktitle, addressAndDate, annotate)
        count = count-1

    print """
%}}}
\end{description}
    """

def printHelp():
    print """
usage: python bibconvert.py --suffix suffix --highlight author1 [--highlight author2] --input 1.bib [--input 2.bib]
suffix can be 'web' or 'cv'
    'web': jemdoc format for personal webpage 
    'cv': latex format for resume 
"""

if __name__ == "__main__":
    suffix = None
    highlightAuthors = []
    filenames = []

    if len(sys.argv) < 3 or sys.argv[1] in ('--help', '-h'):
        printHelp()
        raise SystemExit
    for i in range(1, len(sys.argv), 2):
        if sys.argv[i] == '--suffix':
            if suffix:
                raise RuntimeError("only one suffix can be accepted")
            suffix = sys.argv[i+1]
        elif sys.argv[i] == '--highlight':
            highlightAuthors.append(sys.argv[i+1])
        elif sys.argv[i] == '--input':
            filenames.append(sys.argv[i+1])
        else:
            break

    bibDB = read(filenames, "%")
    #print(bibDB.strings)
    #print(bibDB.entries)
    
    # write 
    printBibDB(bibDB, highlightAuthors, suffix)
