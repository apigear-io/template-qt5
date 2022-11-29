{{- $module_id := printf "%s" (snake .Module.Name) }}
{{- $MODULE_ID := printf "%s" (SNAKE .Module.Name) }}
{{- $module_path := (path .Module.Name) }}
{{- $SOURCES := printf "%s_OLINK_SOURCES" $MODULE_ID -}}

find_package(Qt5 REQUIRED COMPONENTS Core Qml Network WebSockets)

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
  # pull nlohmann json as dependency
  message(STATUS "nlohmann_json NOT FOUND, fetching the release package")
  include(FetchContent)
  set(JSON_Install ON)
  FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.7.3)
  FetchContent_MakeAvailable(json)
endif()

set ({{$MODULE_ID}}_OLINK_SOURCES
    ../../shared/olinkclient.cpp
    olinkfactory.cpp
{{- range .Module.Interfaces }}
    olink{{lower .Name}}.cpp
    olink{{lower .Name}}adapter.cpp
{{- end }}
)

# dynamic library
add_library({{$module_id}}_olink STATIC ${ {{- $SOURCES -}} })
target_include_directories({{$module_id}}_olink PRIVATE ../{{$module_id}})
target_link_libraries({{$module_id}}_olink PRIVATE Qt5::Core Qt5::Qml Qt5::WebSockets {{$module_id}}_api PUBLIC nlohmann_json::nlohmann_json olink_core qtpromise)