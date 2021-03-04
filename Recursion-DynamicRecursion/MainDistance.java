
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.lang.Object;

public class MainDistance extends Distance
{
  public static ArrayList<String> readFileToCorrect(String filename) throws FileNotFoundException, IOException{

    try{
      ArrayList<String> terms = new ArrayList<String>();
      BufferedReader reader = new BufferedReader(new FileReader(filename));
      String line = reader.readLine();

      line = line.replaceAll("\\p{Punct}", "");
      StringTokenizer st = new StringTokenizer(line, " ");

      for(int i=0; st.hasMoreTokens(); i++)
        terms.add(st.nextToken(" ").toLowerCase());

      return terms;
    }catch (FileNotFoundException e) {
            System.out.println("Error file");
            return null;
     }
  }

  public static ArrayList<String> readFileDictionary(String filename) throws FileNotFoundException, IOException{

    try{
      ArrayList<String> terms = new ArrayList<String>();
      BufferedReader reader = new BufferedReader(new FileReader(filename));
      String line = "";

      while ((line = reader.readLine()) != null) {
        if (!line.equals(""))
          terms.add(line);
      }
      return terms;
    }catch (FileNotFoundException e) {
            System.out.println("Error file");
            return null;
     }
  }


  public static void main(String[] args) throws FileNotFoundException, IOException
  {
    ArrayList<String> words = readFileToCorrect(args[0]);
    ArrayList<String> dictionary = readFileDictionary(args[1]);

    int [][] matr;
    int min, temp, i, j;
    long time_0, time_1;
    Distance obj = new Distance();

    int size_word = words.size();
    int size_dictionary = dictionary.size();

    // Start timer for edit_distance_dyn method

    time_0 = System.currentTimeMillis();

    for(i=0; i<size_word; i++){
      j=0;
      obj = new Distance(words.get(i).length()+1, dictionary.get(j).length()+1);
      min = obj.edit_distance_dyn(words.get(i),dictionary.get(j));
      for(j=1; j<size_dictionary; j++){
        obj = new Distance(words.get(i).length()+1, dictionary.get(j).length()+1);
        if(min > (temp = obj.edit_distance_dyn(words.get(i),dictionary.get(j))))
          min = temp;
        // the controlled word exists and it goes to the next word
        else if(temp == 0)
          j = size_dictionary;
      }
      //System.out.println("" + words.get(i) + ": " + min);
    }

    time_1 = System.currentTimeMillis();

    // End timer for edit_distance_dyn method

    System.out.println("edit_distance_dyn execution = " + (time_1-time_0) + " msec.");

    System.out.println("\n ------- \n");

    // Start timer for edit_distance method

    time_0 = System.currentTimeMillis();

    for(i=0; i<size_word; i++){
      j=0;
      min = obj.edit_distance(words.get(i),dictionary.get(j));
      for(j=1; j<size_dictionary; j++){
        if(min > (temp = obj.edit_distance(words.get(i), dictionary.get(j))))
          min = temp;
          // the controlled word exists and it goes to the next word
          else if(temp == 0)
            j = size_dictionary;
      }
      //System.out.println("" + words.get(i) + ": " + min);
    }

    time_1 = System.currentTimeMillis();

    // End timer for edit_distance method

    System.out.println("edit_distance execution = " + (time_1-time_0) + " msec.");
  }
}
