public class Swapper implements Runnable {
    private int offset;
    private Interval interval;
    private String content;
    private char[] buffer;

    public Swapper(Interval interval, String content, char[] buffer, int offset) {
        this.offset = offset;
        this.interval = interval;
        this.content = content;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        char[] contentChar = content.toCharArray();
        int length = interval.getY() - interval.getX() + 1;
        for(int count = 0; count < length; count++){
            buffer[count + offset] = contentChar[count + interval.getX()];
        }
    }
}
