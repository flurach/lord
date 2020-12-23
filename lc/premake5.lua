project "lc"
	kind "SharedLib"
	language "C"

	includedirs {
		(BASE_DIR .. "/lp/src")
	}
	files { "src/**.c" }
