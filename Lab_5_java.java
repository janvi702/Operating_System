import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ReaderWriterDemo {
    private static int sharedData = 0; // Added missing '='
    private static final ReentrantReadWriteLock lock = new ReentrantReadWriteLock(); // Added missing '='
    static class Reader implements Runnable {
        private final int id;

        Reader(int id) {
            this.id = id; // Added missing '='
        }

        @Override
        public void run() {
            lock.readLock().lock();
            try {
                System.out.println("Reader " + id + " reads: " + sharedData); // Fixed string concatenation
            } finally {
                lock.readLock().unlock();
            }
        }
    }
    static class Writer implements Runnable {
        @Override
        public void run() {
            lock.writeLock().lock();
            try {
                sharedData = 100; // Added missing '='
                System.out.println("Writer updates data to: " + sharedData); // Fixed missing quote and concatenation
            } finally {
                lock.writeLock().unlock();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        // Moved thread creation and execution inside the main method
        Thread r1 = new Thread(new Reader(1));
        Thread r2 = new Thread(new Reader(2));
        Thread w1 = new Thread(new Writer());
        Thread r3 = new Thread(new Reader(3));

        r1.start();
        r2.start();
        w1.start();
        r3.start();

        r1.join();
        r2.join();
        w1.join();
        r3.join();

        System.out.println("Final shared data: " + sharedData);
    }
}
