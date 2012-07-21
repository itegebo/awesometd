find . \( -name '*.c' -or -name '*.h' \) -exec grep -H '^#include' {} \; | sed -rn "s%\./([^:]+):#include +([^<].+)%\2;%p" |sort|uniq
dot -Tpng include-graph.dot -o include-graph.png
