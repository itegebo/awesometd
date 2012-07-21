find . \( -name '*.c' -or -name '*.h' \) -exec grep -H '^#include' {} \; | sed -rn "s%\./([^:]+):#include +([^<].+)%"\1" -> \2;%p" > local-include-graph.dot
