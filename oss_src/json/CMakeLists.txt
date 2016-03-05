project(json)

make_library(json
  SOURCES
    json_flexible_type.cpp
  REQUIRES
    flexible_type
)
