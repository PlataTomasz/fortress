@echo off

set /p "build_target=Build target[Client/Server]:"
set /p "is_editor_build=Editor build?[Yes/No]:"
set /p "build_type=Build type[Debug/Release]:"
set /p "platform=Platform[Linux/Windows]:"
SET "build_append_options="

IF [[ "Client"=="%build_target%"* "]]" || [[ "-z" "%build_target%" "]]" (
  SET "build_append_options=extra_suffix"
) ELSE (
  IF [[ "Server" == "%build_target%"* "]]" (
    SET "build_append_options=extra_suffix"
  ) ELSE (
    echo "Error: Invalid build target! Exiting."
    exit "1"
  )
)
IF [[ "Linux" == "%platform%"* "]]" || [[ "-z" "%platform%" "]]" (
  SET "build_append_options="%build_append_options% platform"
) ELSE (
  IF [[ "Windows" == "%platform%"* "]]" (
    SET "build_append_options="%build_append_options% platform"
  ) ELSE (
    echo "Error: Invalid build target! Exiting."
    exit "1"
  )
)
IF [[ "Debug" == "%build_type%"* "]]" || [[ "-z" "%build_type%" "]]" (
  SET "build_append_options="%build_append_options% keep_symbols"
) ELSE (
  IF [[ "Release" == "%build_type%"* "]]" (
    SET "build_append_options="%build_append_options% keep_symbols"
  ) ELSE (
    echo "Error: Invalid build type! Exiting."
    exit "2"
  )
)
IF [[ "Yes" == "%is_editor_build%"* "]]" || [[ "-z" "%is_editor_build%" "]]" (
  SET "build_append_options="%build_append_options% target"
) ELSE (
  IF [[ "No" == "%is_editor_build%"* "]]" (
    SET "build_append_options="%build_append_options% target"
  ) ELSE (
    IF [[ "Template" == "%is_editor_build%"* "]]" (
      SET "build_append_options="%build_append_options% target"
    ) ELSE (
      exit "3"
    )
  )
)
SET "build_append_options="%build_append_options% use_lto"
echo "Building with options: " "%build_append_options%"
cd "%CD%\..\.."
pwd
scons "%build_append_options%"
echo "Build finished!"