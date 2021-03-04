public class ValuePair<A, B>{
    private A first;
    private B second;

    public ValuePair(A first, B second) {
        this.first = first;
        this.second = second;
    }

    public String toString(){return "(" + first + ", " + second + ")";}

    public A getFirst() {return first;}

    public B getSecond(){return second;}
}
