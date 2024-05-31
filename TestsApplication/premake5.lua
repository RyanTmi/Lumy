project "TestsApplication"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "Source/**.hpp", "Source/**.cpp"
    }

    includedirs {
        "%{wks.location}/Engine/Source",
    }

    links {
        "Engine"
    }

    filter { "system:macosx" }
        systemversion "14.0"

        links {
            "Metal.framework",
            "MetalKit.framework",
            "AppKit.framework",
            "Foundation.framework",
            "QuartzCore.framework",
            "GameController.framework",
            "Cocoa.framework",
        }

        xcodebuildsettings {
            ["USE_HEADERMAP"] = "NO",
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES"
        }
    filter {}

    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
    filter {}

    filter { "configurations:Release" }
        runtime "Release"
        optimize "on"
    filter {}
