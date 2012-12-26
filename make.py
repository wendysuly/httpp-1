#!/usr/bin/python

import jmake
import os

jmake.Libraries(
   "jnet",
   "jformat",
   "jhash",
   "boost_thread",
   "boost_regex"
)

jmake.Output("libhttpp.so")

jmake.Standard("gnu++11")

jmake.Compiler("g++")

jmake.Shared()

#jmake.WarnFlags("all", "extra", "ctor-dtor-privacy", "old-style-cast", "overloaded-virtual", "init-self", "missing-include-dirs", "switch-default", "switch-enum", "undef")

jmake.InstallHeaders()
jmake.InstallOutput()

jmake.NoPrecompile(
   "src/html_start.hpp",
   "src/html_end.hpp"
)