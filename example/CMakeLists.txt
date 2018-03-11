add_executable(esgit_example
  main.cpp
)

TARGET_LINK_LIBRARIES(esgit_example
  esgit
  LibGit2::LibGit2
)
