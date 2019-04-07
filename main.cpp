#include <iostream>
#include "UnionFind.h"

template<typename TNodeId>
void dumpUnionFindData(const TUnionFind<TNodeId> & uf)
{
   cout << "nodes:[";
   copy(uf.mNodes.cbegin(), uf.mNodes.cend()-1, ostream_iterator<TNodeId>(cout, ","));
   cout << uf.mNodes.back() << "]" << endl;
   cout << "ranks:[";
   copy(uf.mNodeRanks.cbegin(), uf.mNodeRanks.cend()-1, ostream_iterator<TNodeId>(cout, ","));
   cout << uf.mNodeRanks.back() << "]" << endl;
}

int main()
{
   UnionFind uf(10);
   dumpUnionFindData(uf);
   
   uf.fuse(0, 1);
   dumpUnionFindData(uf);
   
   uf.fuse(2, 3);
   dumpUnionFindData(uf);
   
   uf.fuse(0, 3);
   dumpUnionFindData(uf);

   uf.fuse(4, 5);
   dumpUnionFindData(uf);

   uf.fuse(8, 9);
   dumpUnionFindData(uf);

   uf.fuse(5, 8);
   dumpUnionFindData(uf);

   uf.fuse(0, 8);
   dumpUnionFindData(uf);
   
   assert(uf.find(0) == uf.find(1));
   assert(uf.find(1) == uf.find(2));
   assert(uf.find(2) == uf.find(3));
   assert(uf.find(3) == uf.find(4));
   assert(uf.find(5) == uf.find(8));
   assert(uf.find(0) == uf.find(9));
   dumpUnionFindData(uf);

   return 0;
}