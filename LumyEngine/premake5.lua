project "LumyEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    filter { "action:vs*" }
        pchheader "lmpch.hpp"
        pchsource "src/lmpch.cpp"
    filter {}

    filter { "action:xcode4" }
        pchheader "src/lmpch.hpp"
    filter {}

    filter { "action:cmake" }
        pchheader "Lumy/LumyEngine/src/lmpch.hpp"
    filter {}

    files {
        "src/**.hpp", "src/**.inl",
        "src/**.cpp", "src/**.mm" ,
    }

    includedirs {
        "src",
        "vendor/metal/metal-cpp",
        "vendor/metal/metal-cpp-extension",
    }

    filter { "system:macosx" }
        systemversion "14.0"

        links {
            "Metal.framework",
            "MetalKit.framework",
            "AppKit.framework",
            "Foundation.framework",
            "QuartzCore.framework",

            "MetalCpp"
        }

        xcodebuildsettings {
            ["USE_HEADERMAP"] = "NO",
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES"
        }
    filter {}

    filter { "configurations:Debug" }
        defines "LM_DEBUG"
        runtime "Debug"
        symbols "on"
    filter {}

    filter { "configurations:Release" }
        defines "LM_RELEASE"
        runtime "Release"
        optimize "on"
    filter {}

    filter { "configurations:Dist" }
        defines "LM_DIST"
        runtime "Release"
        optimize "on"
    filter {}
