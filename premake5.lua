workspace "Lumy"
    architecture "universal"
    startproject "LumyEngine"

    configurations { "Debug", "Release", "Dist" }

require "vendor/premake-cmake/cmake"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Core"
    include "LumyEngine"
group ""

group "Misc"
    include "LumyTests"
group ""