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
IncludeDir["Glad"] = "Dooda/vendor/Glad/include"
IncludeDir["ImGui"] = "Dooda/vendor/imgui"
IncludeDir["glm"] = "Dooda/vendor/glm"

--Group the depndancies together
group "Depedencies"
	include "Dooda/vendor/GLFW"
	include "Dooda/vendor/Glad"
	include "Dooda/vendor/imgui"
group ""


project "Dooda"

	location "Dooda"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{prj.name}/vendor/spdlog/include"
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows" 
		systemversion "latest"
		
		defines 
		{
			"DD_PLATFORM_WINDOWS",
			"DD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "DD_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "DD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DD_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{IncludeDir.glm}",
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
		runtime "debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "DD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DD_DIST"
		runtime "Release"
		optimize "on"