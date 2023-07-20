public class FloatDecompose {
    public static int getSign(float value) {
        int bitValue = Float.floatToIntBits(value);
        int signValue = bitValue >>> 31;
        return signValue;
    } 

    public static int getExponent(float value) {
        int bitValue = Float.floatToIntBits(value);
        //Exponent is in bits 23-30
        int exponentBitValue = (bitValue & 0x7F800000) >> 23;
        return exponentBitValue;
    } 

    public static int getFraction(float value) {
        int bitValue = Float.floatToIntBits(value);
        //Mantissa is in bits 0-22
        int mantissaBitValue = (bitValue & 0x007FFFFF);
        return mantissaBitValue;
    } 

    public static float makeFloat(int sign, int exp, int frac) {
        int defaultBit = 0x00000000 | (exp << 23);
        defaultBit |= frac << 0;
        defaultBit |= sign << 31;
        return Float.intBitsToFloat(defaultBit);
    }
}