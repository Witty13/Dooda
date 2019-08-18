workspace "Dooda"
	architecture "x64"
	startproject "Sandbox"
	
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
	 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include diectories relitive to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Dooda/vendor/GLFW/include"

include "Dooda/vendor/GLFW"

project "Dooda"

	location "Dooda"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Ddpch.h"
	pchsource "Dooda/src/Ddpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links 
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows" 
		systemversion "latest"
		
		defines 
		{
			"DD_PLATFORM_WINDOWS",
			"DD_BUILD_DLL"
		}

		postbuildcommands 
		{
			("{COPY} ../bin/" .. outputdir .. "/Dooda/Dooda.dll ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "DD_DEBUG"
		symbols "on"
		
	filter "configurations:Release"
		defines "DD_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "DD_DIST"
		optimize "on"


project "Sandbox"
	
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Dooda/vendor/spdlog/include",
		"Dooda/src"
	}

	links 
	{
		"Dooda"
	}

	filter "system:windows" 
		systemversion "latest"

		defines 
		{
			"DD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DD_DEBUG"
		symbols "on"
		
	filter "configurations:Release"
		defines "DD_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "DD_DIST"
		optimize "on"