import java.util.LinkedList;
import java.util.ArrayList;

public class Graph{
  private int arches;
  private ArrayList<LinkedList<Arch>> adjacencylist = new ArrayList<LinkedList<Arch>>();
  private int cyclenumber;

  Graph(int arches) {
    this.arches = arches;
    for (int u=0; u<arches; u++)    // Create adjacency lists
      adjacencylist.add(new LinkedList<Arch>());
  }

  public LinkedList<Arch> getArches(int source){
    return adjacencylist.get(source);
  }
  public int getArches(){
    return arches;
  }

  /* Delete source -> destination  AND  destination -> source */
  public void removeArch(int source, int destination){
    // Get adjacency lists
    LinkedList<Arch> list1 = adjacencylist.get(source);
    LinkedList<Arch> list2 = adjacencylist.get(destination);
    int sizeFirstArch = list1.size();
    int sizeSecondArch = list2.size();

    // 1)  Delete Source -> Destination
    int i=0;
    boolean stop=false; // Once edge is found, delete and stop while
    while(i<sizeFirstArch && !stop){
      if(list1.get(i).destination == destination){
        list1.remove(i);
        stop = true;
      }
      else
        i++;
    }
    // 2)  Delete destination -> source
    i=0;
    /* If the first cycle didn't find the right edge to delete,
    then we can ignore this cycle */
    while(i<sizeSecondArch && stop){
      if(list2.get(i).destination == source){
        list2.remove(i);
        stop = false;
      }
      else
        i++;
    }
  }
  
  /* adds an arc in the undirected graph */
  public void addArch(int source, int destination, int weight){
    Arch archFistDirection = new Arch(source, destination, weight);
    Arch archSecondDirection = new Arch(destination, source, weight);
    adjacencylist.get(source).addFirst(archFistDirection);
    adjacencylist.get(destination).addFirst(archSecondDirection);
  }

  public int getWeightAt(int source, int destination){
    LinkedList<Arch> list = adjacencylist.get(source);
    int i, size = list.size();

    for(i=0; i<size; i++)
      if(list.get(i).destination == destination)
        return list.get(i).weight;    //  return weight
    return -1;    // fail
  }
}
