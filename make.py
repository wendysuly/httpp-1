#!/usr/bin/python

import jmake

jmake.Libraries(
   "jnet",
   "jformat",
   "jhash",
   "boost_thread"
)

jmake.Output("libhttpp.so")

jmake.Standard("gnu++0x")

jmake.Compiler("g++-4.7")

jmake.Shared()

jmake.WarnFlags("all", "extra", "ctor-dtor-privacy", "old-style-cast", "overloaded-virtual", "init-self", "missing-include-dirs", "switch-default", "switch-enum", "undef")

jmake.InstallHeaders()
jmake.InstallOutput()