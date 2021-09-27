#!/bin/bash

rm -rf '2017-11-28-Jgraph'
tar -xvf '2017-11-28-Jgraph.tar'
cd jgraph 
make
cd ..
rm -rf noteeps
unzip noteeps.zip
rm nmusic
g++ -std=c++11 -o nmusic nmusic.cpp
./nmusic mary.txt mary.jgr
./nmusic g.txt g.jgr
./nmusic juggler.txt juggler.jgr
./jgraph/jgraph -P mary.jgr | ps2pdf - | convert -density 300 - -quality 100 mary.jpg 
./jgraph/jgraph -P g.jgr | ps2pdf - | convert -density 300 - -quality 100 g.jpg 
./jgraph/jgraph -P juggler.jgr | ps2pdf - | convert -density 300 - -quality 100 juggler.jpg 
