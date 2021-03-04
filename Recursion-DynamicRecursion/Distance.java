import java.io.*;

public class Distance
{
    public int [][] matr;
    public int i, j;

    public Distance(){}

    public Distance(int row, int column)
    {
      matr = new int[row][column];
      i = 0;
      j = 0;
    }

    public static String rest(String s)
    {return s.substring(1, s.length());}

    private int min(int d1, int d2)
    {return (d1 <= d2)? d1 : d2;}

  	public int edit_distance(String s1, String s2)
  	{
  		  if(s1.length()==0)
            return s2.length();
        else if(s2.length()==0)
            return s1.length();
        else
        {
            if(s1.charAt(0) == s2.charAt(0))
                return min(edit_distance(rest(s1), rest(s2)),
                       min(1 + edit_distance(s1, rest(s2)),
                       1 + edit_distance(rest(s1), s2)));
            else
                return min(1 + edit_distance(s1, rest(s2)),
                        1 + edit_distance(rest(s1), s2));
        }
  	}
    
    public int edit_distance_dyn(String s1, String s2)
    {
      if(s1.length()==0)
          return s2.length();
      else if(s2.length()==0)
          return s1.length();
      else{
        // first row initialization
        if(i==0){
          matr[i][j] = j;
          if(j<s2.length()){
            j++;
            return edit_distance_dyn(s1, s2);
          }
          else{
            i++; j=0;
            return edit_distance_dyn(s1, s2);
          }
        }
        // first column initialization
        else if(j==0){
          matr[i][j] = i; j++;
          return edit_distance_dyn(s1, s2);
        }
        else{
          // distance calculation
          if(s1.charAt(i-1) == s2.charAt(j-1))
            matr[i][j] = min(matr[i-1][j-1], min(matr[i-1][j]+1, matr[i][j-1]+1));
          else
            matr[i][j] = min(matr[i][j-1]+1, matr[i-1][j]+1);

          // movement choice
          if(j<s2.length()){
            j++;
            return edit_distance_dyn(s1, s2);
          }
          else if(i<s1.length()){
            i++; j=0;
            return edit_distance_dyn(s1, s2);
          }
          else
            return matr[i][j];
        }
      }
    }
}
