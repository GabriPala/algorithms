import org.junit.Test;
import static org.junit.Assert.*;

public class TestDistance extends Distance
{
    private int[][] matr;
    Distance obj_ed = new Distance();
    Distance obj_edd;

    @Test
    public void testDistanceEmptyStringEd() throws Exception
    {
        String a = "";
        String b = "casa";

        assertSame("FAIL 1", 4, obj_ed.edit_distance(a,b));
        assertSame("FAIL 2", 4, obj_ed.edit_distance(b,a));
    }

    @Test
    public void testDistanceEqualStringEd() throws Exception
    {
      String a = "casa";
      assertSame("FAIL 1", 0, obj_ed.edit_distance(a,a));
    }

    @Test
    public void testDistanceEmptyStringEdd() throws Exception
    {
      String a = "";
      String b = "casa";
      obj_edd = new Distance(a.length()+1, b.length()+1);
      assertSame("FAIL 1", 4, obj_edd.edit_distance_dyn(a,b));
      assertSame("FAIL 2", 4, obj_edd.edit_distance_dyn(b,a));
    }

    @Test
    public void testDistanceEqualStringEdd() throws Exception
    {
      String a = "casa";
      obj_edd = new Distance(a.length()+1, a.length()+1);
      assertSame("FAIL 1", 0, obj_edd.edit_distance_dyn(a,a));
    }

    @Test
    public void testDistanceStringEd() throws Exception
    {
        String a = "casa";
        String b = "cassa";
        String f = "tassa";
        String g = "passato";

        assertSame("FAIL 4", 1, obj_ed.edit_distance(a,b));
        assertSame("FAIL 7", 4, obj_ed.edit_distance(f,g));
    }

    @Test
    public void testDistanceStringEdd() throws Exception
    {
        String a = "casa";
        String b = "cassa";
        String f = "tassa";
        String g = "passato";
        obj_edd = new Distance(a.length()+1, b.length()+1);
        assertSame("FAIL 4", 1, obj_edd.edit_distance_dyn(a,b));
        obj_edd = new Distance(f.length()+1, g.length()+1);
        assertSame("FAIL 7", 4, obj_edd.edit_distance_dyn(f,g));
    }
}
