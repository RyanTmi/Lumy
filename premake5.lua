workspace "Lumy"
    architecture "ARM64"
    startproject "LumyEngine"

    configurations { "Debug", "Release", "Dist" }

require "vendor/premake-cmake/cmake"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "LumyEngine/vendor/metal"
group ""

group "Core"
    include "LumyEngine"
group ""

group "Tests"
    include "LumyTests"
group ""
