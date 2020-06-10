project("RVAUpdater" LANGUAGES CSharp)
set(PROJECT_DIR ${WOTWR_PROJECTS_DIR}/${PROJECT_NAME})

include(CSharpUtilities)

set(
	SOURCE_FILES
	"RVAUpdate.cs"
)

set(
	REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Core"
    "System.Data"
    "System.Xml"
    "System.Xml.Linq"
)

add_executable(${PROJECT_NAME}
	${SOURCE_FILES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES ${REFERENCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCE_Newtonsoft.Json ${WOTWR_LIB_DIR}/Newtonsoft.Json.dll)

set(CMAKE_CSharp_FLAGS "/langversion:latest")

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
		VERSION ${WORWR_VERSION}
		SOVERSION ${WORWR_MAJOR_VERSION}
		FOLDER csharp
		VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2"
)