import java.util.concurrent.locks.ReentrantReadWriteLock;

// Shared Resource Class
class SharedResource {
    private String data = "Initial Base Data";
    
    // ReadWriteLock manages separate locks for reading and writing
    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

    // Reader method
    public void read(String readerName) {
        lock.readLock().lock(); // Acquire read lock (allows concurrent readers)
        try {
            System.out.println("[READ] " + readerName + " acquired Read Lock. Current Data: \"" + data + "\"");
            Thread.sleep(100); // Simulate reading time
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            System.out.println("[RELEASE] " + readerName + " released Read Lock.");
            lock.readLock().unlock();
        }
    }

    // Writer method
    public void write(String writerName, String newData) {
        lock.writeLock().lock(); // Acquire write lock (exclusive access)
        try {
            System.out.println("[WRITE] >>> " + writerName + " acquired Write Lock. Updating data to: \"" + newData + "\"");
            data = newData;
            Thread.sleep(150); // Simulate writing time
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            System.out.println("[RELEASE] <<< " + writerName + " released Write Lock.");
            lock.writeLock().unlock();
        }
    }
}

// Reader Thread
class ReaderTask implements Runnable {
    private final SharedResource resource;
    private final String name;

    public ReaderTask(SharedResource resource, String name) {
        this.resource = resource;
        this.name = name;
    }

    @Override
    public void run() {
        for (int i = 0; i < 2; i++) { // Each reader reads twice
            resource.read(name);
            try {
                Thread.sleep(120); // Pause between reads
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

// Writer Thread
class WriterTask implements Runnable {
    private final SharedResource resource;
    private final String name;

    public WriterTask(SharedResource resource, String name) {
        this.resource = resource;
        this.name = name;
    }

    @Override
    public void run() {
        for (int i = 0; i < 2; i++) { // Each writer writes twice
            String newData = "Data updated by " + name + " (Rev " + (i + 1) + ")";
            resource.write(name, newData);
            try {
                Thread.sleep(200); // Pause between writes
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

public class ReaderWriterDemo {
    public static void main(String[] args) {
        SharedResource resource = new SharedResource();

        // Create 3 Reader threads and 2 Writer threads
        Thread r1 = new Thread(new ReaderTask(resource, "Reader-1"));
        Thread r2 = new Thread(new ReaderTask(resource, "Reader-2"));
        Thread r3 = new Thread(new ReaderTask(resource, "Reader-3"));

        Thread w1 = new Thread(new WriterTask(resource, "Writer-1"));
        Thread w2 = new Thread(new WriterTask(resource, "Writer-2"));

        // Start all threads
        r1.start();
        w1.start();
        r2.start();
        w2.start();
        r3.start();

        // Wait for all threads to complete
        try {
            r1.join();
            r2.join();
            r3.join();
            w1.join();
            w2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("\n=== ALL READERS AND WRITERS FINISHED EXECUTION ===");
    }
}
