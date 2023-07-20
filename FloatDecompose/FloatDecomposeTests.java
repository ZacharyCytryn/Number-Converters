import static org.junit.Assert.assertEquals;
import org.junit.Test;

public class FloatDecomposeTests {
    @Test
    public void test_getSign1() {
        assertEquals(1, FloatDecompose.getSign(-93.125f));
    }

    @Test
    public void test_getSign2() {
        assertEquals(0, FloatDecompose.getSign(1.75f));
    }

    @Test
    public void test_getSign3() {
        assertEquals(0, FloatDecompose.getSign(0.578125f));
    }

    @Test
    public void test_getExponent1() {
        assertEquals(133, FloatDecompose.getExponent(-93.125f));
    }

    @Test
    public void test_getExponent2() {
        assertEquals(127, FloatDecompose.getExponent(1.75f));
    }

    @Test
    public void test_getExponent3() {
        assertEquals(126, FloatDecompose.getExponent(0.578125f));
    }

    @Test
    public void test_getFraction1() {
        assertEquals(3817472, FloatDecompose.getFraction(-93.125f));
    }

    @Test
    public void test_getFraction2() {
        assertEquals(6291456, FloatDecompose.getFraction(1.75f));
    }

    @Test
    public void test_getFraction3() {
        assertEquals(1310720, FloatDecompose.getFraction(0.578125f));
    } 
    
    @Test
    public void test_makeFloat1() {
        assertEquals(-93.125f, FloatDecompose.makeFloat(1, 133, 3817472), 0.0000001f);
    }

    @Test
    public void test_makeFloat2() {
        assertEquals(1.75f, FloatDecompose.makeFloat(0, 127, 6291456), 0.0000001f);
    }

    @Test
    public void test_makeFloat3() {
        assertEquals(0.578125f, FloatDecompose.makeFloat(0, 126, 1310720), 0.0000001f);
    }
}