#!/bin/bash
read -p 'Build target[Client/Server]: ' build_target
read -p 'Editor build?[Yes/No]: ' is_editor_build
read -p 'Build type[Debug/Release]: ' build_type
read -p 'Platform[Linux/Windows]: ' platform

build_append_options=""

# # Server - Debug
# "scons target=editor extra_suffix=server use_lto=no modules_artifact_seekers=true keep_symbols=true debug_game=true game_target=server"
# # Server - Engine debug
# "scons target=editor extra_suffix=server use_lto=no dev_build=true debug_symbols=true modules_artifact_seekers=true debug_game=true game_target=server"
# # Server - Release
# "scons target=release use_lto=yes game_target=server"
# # Client - Debug
# "scons target=editor extra_suffix=client use_lto=no modules_artifact_seekers=true keep_symbols=true debug_game=true game_target=client"
# # Client - Engine debug
# "scons target=editor extra_suffix=client use_lto=no dev_build=true debug_symbols=true modules_artifact_seekers=true game_target=client"
# # Client - Release
# "scons target=release use_lto=yes game_target=client"
if [[ "Client" == "$build_target"* ]] || [[ -z "$build_target" ]];
then
	build_append_options="extra_suffix=client game_target=client"
elif [[ "Server" == "$build_target"* ]];
then
	build_append_options="extra_suffix=server game_target=server"
else
	echo "Error: Invalid build target! Exiting."
	exit 1
fi

if [[ "Linux" == "$platform"* ]] || [[ -z "$platform" ]];
then
	build_append_options="$build_append_options platform=linuxbsd"
elif [[ "Windows" == "$platform"* ]];
then
	build_append_options="$build_append_options platform=windows"
else
	echo "Error: Invalid build target! Exiting."
	exit 1
fi

if [[ "Debug" == "$build_type"* ]] || [[ -z "$build_type" ]];
then
	build_append_options="$build_append_options keep_symbols=true debug_game=true"
elif [[ "Release" == "$build_type"* ]];
then
	build_append_options="$build_append_options keep_symbols=false debug_game=false"
else
	echo "Error: Invalid build type! Exiting."
	exit 2
fi

if [[ "Yes" == "$is_editor_build"* ]] || [[ -z "$build_type" ]];
then
	build_append_options="$build_append_options target=editor"
elif [[ "No" == "$is_editor_build"* ]];
then
	build_append_options="$build_append_options target=release"
else
	exit 3
fi

build_append_options="$build_append_options use_lto=yes"


echo "Building with options: " $build_append_options

cd ../..
pwd
scons $build_append_options


echo "Build finished!"
