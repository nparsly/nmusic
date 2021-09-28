#!/bin/bash

if [ "$#" -lt 2 ]; then	
	
	echo "usage: musicmake.sh <input file> <output name>"
	exit
fi

IFILE=$1
OFILE="$2.jgr"
OPIC="$2.jpg"

./nmusic $IFILE $OFILE

./jgraph/jgraph -P $OFILE | ps2pdf - | convert -density 300 - -quality 100 $OPIC

