#!/usr/bin/python

import jmake
import sys

jmake.Libraries (
   "jnet",
   "jhash",
   "jformat",
   "boost_thread"
)

jmake.Output("libhttpp.so")

jmake.Standard("gnu++0x")

jmake.Compiler("g++-4.7")

jmake.Shared()

jmake.WarnFlags("all", "extra", "ctor-dtor-privacy", "old-style-cast", "overloaded-virtual", "init-self", "missing-include-dirs", "switch-default", "switch-enum", "undef")
