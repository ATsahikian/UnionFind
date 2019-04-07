#ifndef UNION_FIND
#define UNION_FIND

#include <vector>
#include <cassert>
#include <iterator>
#include <numeric>

using namespace std;

/*
   Lazy implementation of UnionFind by rank and path compression optimizations.
   Amortized time complexity is O(mlog*n), n - number of nodes, m - amount of fuse and find operation.
   log* - stands for log star not multiplication. Worst case for single operation is O(log n).
*/

template <typename TNodeId = size_t>
class TUnionFind
{
public:

   TUnionFind(size_t nodeNumber)
      : mNodes(nodeNumber)
      , mNodeRanks(nodeNumber, 0)
   {
      iota(mNodes.begin(), mNodes.end(), 0);
   }

   int /*leaderNodeId*/ find(const TNodeId nodeId)
   {
      assert(nodeId < mNodes.size() && nodeId >= 0);

      auto leaderNodeId = nodeId;
      while (mNodes[leaderNodeId] != leaderNodeId) leaderNodeId = mNodes[leaderNodeId];

      // make path compression
      mNodes[nodeId] = leaderNodeId;
      return leaderNodeId;
   }

   void fuse(const TNodeId nodeId1, const TNodeId nodeId2)
   {
      assert(nodeId1 < mNodes.size() && nodeId1 >= 0);
      assert(nodeId2 < mNodes.size() && nodeId2 >= 0);

      const auto leaderNodeId1 = find(nodeId1);
      const auto leaderNodeId2 = find(nodeId2);

      if (leaderNodeId1 != leaderNodeId2)
      {
         if (mNodeRanks[leaderNodeId1] == mNodeRanks[leaderNodeId2])
         {
            mNodeRanks[leaderNodeId1]++;
            mNodes[leaderNodeId2] = leaderNodeId1;
         }
         else if (mNodeRanks[leaderNodeId1] < mNodeRanks[leaderNodeId2])
         {
            mNodes[leaderNodeId1] = leaderNodeId2;
         }
         else
         {
            mNodes[leaderNodeId2] = leaderNodeId1;
         }
      }
   }

private:
   template<typename TNodeId>
   friend void dumpUnionFindData(const TUnionFind<TNodeId> & uf);
   /*
      - Index corresponds to nodeId.
      - Value coresponds to leaderNodeId.
      - NodeId always starts with zero.
   */
   vector<TNodeId> mNodes;
   /*
      - Index corresponds to nodeId.
      - Value is a rank of the node.
   */
   vector<size_t> mNodeRanks;
};

using UnionFind = TUnionFind<>;

#endif
