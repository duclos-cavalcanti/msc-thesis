#!/bin/bash

MD=$1
PDF=$2
HTML="TMP.html"

pandoc -s -f markdown -t html -o ${HTML} ${MD} 2> /dev/null
wkhtmltopdf -q ${HTML} ${2} 2> /dev/null

[ -f ${HTML} ] && rm -f ${HTML}
