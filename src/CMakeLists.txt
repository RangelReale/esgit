SET(INC_DIR ../include)

add_library(esgit STATIC
  Init.cpp
  Exception.cpp
  Buffer.cpp
  OId.cpp
  Object.cpp
  Repository.cpp
  Commit.cpp
  Tree.cpp
  TreeEntry.cpp
  Blob.cpp
  Signature.cpp
  RevWalk.cpp
  Util.cpp

  ${INC_DIR}/esgit/ESGit.h
  ${INC_DIR}/esgit/Init.h
  ${INC_DIR}/esgit/Exception.h
  ${INC_DIR}/esgit/Buffer.h
  ${INC_DIR}/esgit/OId.h
  ${INC_DIR}/esgit/Object.h
  ${INC_DIR}/esgit/Repository.h
  ${INC_DIR}/esgit/Commit.h
  ${INC_DIR}/esgit/Tree.h
  ${INC_DIR}/esgit/TreeEntry.h
  ${INC_DIR}/esgit/Blob.h
  ${INC_DIR}/esgit/Signature.h
  ${INC_DIR}/esgit/RevWalk.h
  ${INC_DIR}/esgit/Util.h
)
