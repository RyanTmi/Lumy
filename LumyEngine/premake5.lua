project "LumyEngine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    -- filter { "action:vs*" }
    --     pchheader "lmpch.hpp"
    --     pchsource "src/LumyEngine/lmpch.cpp"
    -- filter {}

    -- filter { "action:xcode4" }
    --     pchheader "src/LumyEngine/lmpch.hpp"
    -- filter {}

    -- filter { "action:cmake" }
    --     pchheader "Lumy/LumyEngine/src/LumyEngine/lmpch.hpp"
    -- filter {}

    defines {
        "LM_EXPORT"
    }

    files {
        "src/**.hpp", "src/**.inl",
        "src/**.cpp", "src/**.mm" ,
    }

    includedirs {
        "src",
        "vendor/MetalCpp/Include",
    }

    postbuildcommands {
        "{MKDIR} %{cfg.buildtarget.directory}/../LumyTests",
        "{COPYFILE} %{cfg.buildtarget.relpath} %{cfg.buildtarget.directory}/../LumyTests"
    }

    filter { "system:macosx" }
        systemversion "14.0"

        files {
            "%{wks.location}/assets/shaders/*.metal"
        }

        links {
            "Metal.framework",
            "MetalKit.framework",
            "AppKit.framework",
            "Foundation.framework",
            "QuartzCore.framework",
            "GameController.framework",

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
