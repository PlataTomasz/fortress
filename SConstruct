#!/usr/bin/env python
import os
import sys

src_dir = "src/"
cl_src_dir = src_dir+"client/"
sv_src_dir = src_dir+"server/"
sh_src_dir = src_dir+"shared/"

env = SConscript("godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/", "godot-cpp/src/", "godot-cpp/gen/include/godot_cpp/","godot-cpp/include/godot_cpp"])

sources = Glob("src/*.cpp")

sources += Glob(cl_src_dir+"*.cpp")
sources += Glob(cl_src_dir+"status_effects/*.cpp")
sources += Glob(cl_src_dir+"status_effects/mercenaries/tundra/*.cpp")

sources += Glob(cl_src_dir+"entities/*.cpp")
sources += Glob(cl_src_dir+"entities/mercenaries/*.cpp")
sources += Glob(cl_src_dir+"entities/mercenaries/tundra/*.cpp")
sources += Glob(cl_src_dir+"entities/mercenaries/fist_mercenary/*.cpp")
sources += Glob(cl_src_dir+"game_logic/abilities/*.cpp")
sources += Glob(cl_src_dir+"game_logic/abilities/tundra/*.cpp")
sources += Glob(cl_src_dir+"game_logic/abilities/fist_mercenary/*.cpp")
sources += Glob(cl_src_dir+"ui/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "client/bin/libgdexample.{}.{}.framework/libgdexample.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "client/bin/libgdexample{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
