workspace "Lumy"
    configurations { "Debug", "Release" }
    startproject "LumyEngine"

    filter { "system:macosx" }
        architecture "ARM64"
    filter {}

    filter { "system:windows or linux" }
        architecture "x86_64"
    filter {}

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
