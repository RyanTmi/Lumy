project "engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    defines {
        "LM_EXPORT"
    }

    files {
        "source/**.hpp", "source/**.cpp", "source/**.mm" ,
    }

    includedirs {
        "source",
        "vendor/metal-cpp/include",
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

            "metal-cpp"
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
