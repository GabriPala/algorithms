import java.util.*;

public class Prim{

  static class ParentNode{
    int parent;
    int weight;
  }

  public long PrimMST(Graph g){
    int arches = g.getArches(), i;
    boolean[] mst = new boolean[arches];
    ParentNode[] parentNode = new ParentNode[arches];
    int[] keys = new int[arches];

    for(i=0; i<arches; i++) {
      keys[i] = Integer.MAX_VALUE;    // this is same infinity
      parentNode[i] = new ParentNode();
    }

    // initialize priority queue and override a copare method first and second node
    PriorityQueue<ValuePair<Integer, Integer>> pq = new PriorityQueue<>(arches, new Comparator<ValuePair<Integer, Integer>>() {
      @Override
      public int compare(ValuePair<Integer, Integer> p1, ValuePair<Integer, Integer> p2){
        int k1 = p1.getFirst();
        int k2 = p2.getFirst();
        return k1-k2;
      }
    });

    // create the pair for the first index, 1 key 1 index
    keys[1] = 0;
    ValuePair<Integer, Integer> firstPair = new ValuePair<>(keys[1], 1);
    pq.offer(firstPair);
    parentNode[1] = new ParentNode();
    parentNode[1].parent = -1;

    while(!pq.isEmpty()){
      // extract min value, this is the fist and does a pop
      ValuePair<Integer, Integer> extractedPair = pq.poll();
      int extractedNode = extractedPair.getSecond();
      mst[extractedNode] = true;
      LinkedList<Arch> list = g.getArches(extractedNode);
      int size = list.size();

      for(i=0; i<size; i++){
        Arch e = list.get(i);
        if(!mst[e.destination]){ // enter into the "if" only if it has not yet passed through that node
          if(keys[e.destination]>e.weight){ // check if the new weight is better than old
            ValuePair<Integer, Integer> pair = new ValuePair<>(e.weight, e.destination);
            pq.offer(pair);   // insert a new pair in the queue
            parentNode[e.destination].parent = extractedNode;
            parentNode[e.destination].weight = e.weight;
            keys[e.destination] = e.weight;
          }
        }
      }
    }

    long totalWeight = 0;
    for (i=1; i<arches; i++)
      totalWeight+=parentNode[i].weight; // calculate total MST weight
    return totalWeight;
  }
}
