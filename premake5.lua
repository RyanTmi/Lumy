require "vendor/premake/cmake/cmake"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "lumy"
    -- location "./"
    configurations { "Debug", "Release" }
    startproject "engine"

    filter { "system:macosx" }
        architecture "ARM64"
    filter {}

    filter { "system:windows or linux" }
        architecture "x86_64"
    filter {}


    group "dependencies"
        include "engine/vendor/metal-cpp"
    group ""

    group "core"
        include "engine"
    group ""

    group "tests"
        include "tests"
    group ""
