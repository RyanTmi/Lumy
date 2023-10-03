project "LumyEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
    }

    filter "system:macosx"
        systemversion "14.0"

    filter "configurations:Debug"
        defines "LM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LM_DIST"
        runtime "Release"
        optimize "on"
