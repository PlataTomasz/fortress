import sys
import os

build_target = input("Build target[Client/Server]:")
is_editor_build = input("Editor build?[Yes/No]:")
build_type = input("Build type[Debug/Release]:")
platform = input("Platform[Linux/Windows]:")

build_append_options=""

if not build_target or build_target[0] == "Client"[0]:
    build_append_options="extra_suffix=client game_target=client"
elif build_target[0] == "Server"[0]:
    build_append_options="extra_suffix=server game_target=server"
else:
    print("Error: Invalid build target! Exiting!")
    exit(1)
    
if not platform or platform[0] == "Linux"[0]:
	build_append_options = build_append_options + " platform=linuxbsd"
elif platform[0] == "Windows"[0]:
	build_append_options = build_append_options + " platform=windows"
else:
	print("Error: Invalid platform! Exiting.")
	exit(2)

if not build_type or build_type[0] == "Debug"[0]:
	build_append_options = build_append_options + " keep_symbols=true debug_game=true"
elif build_type[0] == "Release"[0]:
	build_append_options = build_append_options + " keep_symbols=false debug_game=false"
else:
	print("Error: Invalid build type! Exiting.")
	exit(3)
    
if not is_editor_build or is_editor_build[0] == "Yes"[0]:
	build_append_options = build_append_options + " target=editor"
elif is_editor_build[0] == "No"[0]:
	build_append_options = build_append_options + " target=release"
elif is_editor_build[0] == "Template"[0]:
	build_append_options = build_append_options + " target=template_release"
else:
	print("Error: Is neither editor build nor release or template! Exiting.")
	exit(4)

build_append_options = build_append_options + " use_lto=yes"
    
print("Building with options: " + build_append_options)

os.chdir("../..")
print(os.getcwd())
print("Build command: " + "scons " + build_append_options)
os.system("scons " + build_append_options)

print("Build finished!")