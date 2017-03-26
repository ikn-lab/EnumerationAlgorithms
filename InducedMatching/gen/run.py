#!/usr/bin/env python
# -*- coding: utf-8 -*-
import time, os, sys, signal
from os.path import join,getsize
import datetime
import commands
import sys

for i in xrange(2, 17):
    for j in ["random", "no_short_cycle"]:
        density = i*0.5
        str_density = '{0:.02f}'.format(density)
        print "./generator " + j + " " + str_density
        commands.getoutput("./generator " + j + " " + str(density))                        
