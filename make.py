#!/usr/bin/python

import jmake
import os

jmake.Libraries(
   "sprawl_format",
   "boost_thread",
   "boost_regex"
)

jmake.Output("libhttpp.so")

jmake.Standard("c++11")

jmake.Compiler("clang++")

jmake.Shared()

#jmake.WarnFlags("all", "extra", "ctor-dtor-privacy", "old-style-cast", "overloaded-virtual", "init-self", "missing-include-dirs", "switch-default", "switch-enum", "undef")

jmake.InstallHeaders()
jmake.InstallOutput()

jmake.NoPrecompile(
   "src/html_start.hpp",
   "src/html_end.hpp"
)
