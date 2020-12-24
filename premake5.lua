workspace "lord"
	configurations { "debug", "release" }
	warnings "extra"

	ROOT_DIR = path.getabsolute(".")
	targetdir (ROOT_DIR .. "/_bin")
	objdir (ROOT_DIR .. "/_bin/obj")

	filter "configurations:debug"
		symbols "on"

	filter "configurations:release"
		optimize "on"

	project "lp"
		kind "SharedLib"
		language "C"

		includedirs { "lp" }
		files { "lp/**.c" }


	project "lc"
		kind "SharedLib"
		language "C"

		includedirs { "lc", "lp" }
		files { "lc/**.c" }


	project "cli"
		kind "ConsoleApp"
		language "C"

		targetname "lord"

		includedirs { "cli", "lc", "lp" }
		files { "cli/**.c" }
		links { "lc", "lp" }
