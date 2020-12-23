project "lc"
	kind "SharedLib"
	language "C"

	includedirs {
		"src",
		(BASE_DIR .. "/lp/src")
	}
	files { "src/**.c" }
