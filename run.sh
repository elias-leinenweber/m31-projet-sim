#!/bin/sh

make && ./out/main > res.csv && Rscript plot.R
