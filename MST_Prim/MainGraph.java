import java.util.ArrayList;
import java.io.*;

public class MainGraph{

  static void WriteTo(String pathname, String S){

    try{
		FileWriter fstream = new FileWriter(pathname, true);
		BufferedWriter out = new BufferedWriter(fstream);

		out.write(S);     // Writes the string S
		out.newLine();

		out.close();		  // Close buffer writer
    }catch (IOException e) {
        e.printStackTrace();
    }
  }

  static ArrayList<Integer> readArches(String pathname){
    if(new File(pathname).exists()){
      BufferedReader br=null;

      /* The first character is the number of nodes
         i = source, i+1 = destination, i+2 = weight; */
      ArrayList<Integer> numbers = new ArrayList<Integer>();
      try{
        br=new BufferedReader(new FileReader(pathname));
        String line = br.readLine();
        while (line != null){
          String[] integersInString=line.split(" ");
          /* Reads one word at a time */
          for(int i=0; i<integersInString.length; i++)
            numbers.add(Integer.parseInt(integersInString[i]));
          line = br.readLine();       // Reads the next line
        }
        br.close();                   // Close buffer writer
      }catch (IOException e){
          e.printStackTrace();
      }
      return numbers;
    }
    else
      return null;                    // The file does not exist
  }


  public static void main(String[] args){

    String allOutput = args[1];
    ArrayList<Integer> allInput;
    int alternatives, i, j=1, arches;
    long originalWeight;
    long time_0, time_1;
    Graph graph;
    Prim mstprim = new Prim();

    /* Read all graph's arches in the input file */
    allInput = readArches(args[0]);
    arches = allInput.get(0);
    graph = new Graph(arches+1);

    /* Start create graph */
    // i = 1 because first value is the vertices' number
    for(i=1; i<arches; i++){
      // j = source, j+1 = destination, j+2 = weight
      graph.addArch(allInput.get(j), allInput.get(j+1), allInput.get(j+2));
      j=j+3;
    }
    /* End create grath */

    /* Read the new arches' number */
    alternatives = allInput.get(j);
    j++;

    originalWeight = mstprim.PrimMST(graph);

    time_0 = System.currentTimeMillis();
    /* Read each alternative of arch */
    for(i=0; i<alternatives; i++){
        graph.addArch(allInput.get(j), allInput.get(j+1), allInput.get(j+2));
        long newWeight = mstprim.PrimMST(graph);
        if(Long.compare(originalWeight, newWeight)>0)
          WriteTo(allOutput, "YES");
        else
          WriteTo(allOutput, "NO");
        graph.removeArch(allInput.get(j), allInput.get(j+1));
        j=j+3;
      }
    time_1 = System.currentTimeMillis();
    System.out.println("Time to control = " + (time_1-time_0) + " msec.");
  }
}
