local vulkan_sdk = os.getenv("VULKAN_SDK")

project "Engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediate/" .. outputdir .. "/%{prj.name}")

    defines {
        "LM_EXPORT"
    }

    files {
        "Source/**.hpp", "Source/**.cpp", "Source/**.mm",
    }

    includedirs {
        "Source",
        "Vendor/metal-cpp/Include",

        vulkan_sdk .. "/include",
    }

    libdirs {
        vulkan_sdk .. "/lib",
    }

    filter { "system:macosx" }
        systemversion "14.0"

        files {
            "%{wks.location}/Assets/Shaders/Metal/*.metal"
        }

        links {
            "Metal.framework",
            "MetalKit.framework",
            "AppKit.framework",
            "Foundation.framework",
            "QuartzCore.framework",
            "Cocoa.framework",

            "libvulkan.dylib",
            "libvulkan.1.dylib",
            "metal-cpp",
        }

        embed {
            "libvulkan.dylib",
            "libvulkan.1.dylib",
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
