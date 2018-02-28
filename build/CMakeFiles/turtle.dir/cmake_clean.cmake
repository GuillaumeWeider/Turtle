FILE(REMOVE_RECURSE
  "turtle-parser.c"
  "turtle-parser.h"
  "turtle-lexer.c"
  "CMakeFiles/turtle.dir/turtle.c.o"
  "CMakeFiles/turtle.dir/turtle-ast.c.o"
  "CMakeFiles/turtle.dir/turtle-parser.c.o"
  "CMakeFiles/turtle.dir/turtle-lexer.c.o"
  "turtle.pdb"
  "turtle"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/turtle.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
