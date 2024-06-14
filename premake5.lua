require "Vendor/Premake/CMake/cmake"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Lumy"
    -- location "./"
    configurations { "Debug", "Release" }
    startproject "Engine"

    filter { "system:macosx" }
        architecture "ARM64"
    filter {}

    filter { "system:windows or linux" }
        architecture "x86_64"
    filter {}


    group "Dependencies"
        include "Engine/Vendor/metal-cpp"
    group ""

    group "Core"
        include "Engine"
    group ""

    group "Tests"
        include "TestsApplication"
    group ""
