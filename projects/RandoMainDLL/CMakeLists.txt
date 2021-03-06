project("RandoMainDLL" LANGUAGES CSharp)
set(PROJECT_DIR ${WOTWR_PROJECTS_DIR}/${PROJECT_NAME})

include(CSharpUtilities)

set(
	SOURCE_FILES
	"AHK.cs"
	"CppCallbacks.cs"
	"Extensions.cs"
	"HintsController.cs"
	"InterOp.cs"
	"LocData.cs"
	"Pickup.cs"
	"Randomizer.cs"
	"RVAFinder.cs"
	"SaveController.cs"
	"SeedController.cs"
	"ShopController.cs"
	"TrackFileController.cs"
	"UberStateController.cs"
	
	"IL2Cpp/BinaryStream.cs"
	"IL2Cpp/Il2CppClass.cs"
	"IL2Cpp/Il2CppData.cs"
	"IL2Cpp/Il2CppDecompiler.cs"
	"IL2Cpp/Il2CppExecutor.cs"
	"IL2Cpp/Il2CppReader.cs"
	"IL2Cpp/Metadata.cs"
	"IL2Cpp/MetadataClass.cs"
	"IL2Cpp/PE.cs"
	"IL2Cpp/PlusSearch.cs"
	
	"Memory/Ability.cs"
	"Memory/AreaType.cs"
	"Memory/GameState.cs"
	"Memory/InventoryItem.cs"
	"Memory/MemoryManager.cs"
	"Memory/MemoryReader.cs"
	"Memory/MessageDescriptor.cs"
	"Memory/ProgramPointer.cs"
	"Memory/Screen.cs"
	"Memory/Shard.cs"
	"Memory/Stats.cs"
	"Memory/UberState.cs"
	"Memory/Vector2.cs"
	"Memory/Vector4.cs"
)

set(
	MISC_FILES
	"Properties/AssemblyInfo.cs"
	".editorconfig"
	"CMakeLists.txt"
)

set(
	REFERENCES
    "Microsoft.CSharp"
    "System"
	"System.Core"
)

add_library(${PROJECT_NAME} SHARED
	${SOURCE_FILES}
	${MISC_FILES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE FALSE)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES ${REFERENCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCE_Newtonsoft.Json ${WOTWR_LIB_DIR}/Newtonsoft.Json.dll)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCE_AutoHotkey.Interop ${WOTWR_LIB_DIR}/AutoHotkey.Interop.dll)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_PACKAGE_REFERENCES "MSBuild.ILMerge.Task_1.1.3")

target_compile_options(${PROJECT_NAME}
    PRIVATE /unsafe
    PRIVATE /platform:x64
)

set(CMAKE_CSharp_FLAGS "/langversion:latest")

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
		VERSION ${WORWR_VERSION}
		SOVERSION ${WORWR_MAJOR_VERSION}
		FOLDER csharp
		DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2"
)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "${WOTWR_INSTALL_DIR}"
	LIBRARY DESTINATION "${WOTWR_INSTALL_DIR}"
	ARCHIVE DESTINATION "${WOTWR_INSTALL_DIR}"
)
