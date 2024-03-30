class BoundedBlockingQueue {
    
    private final ReadWriteLock lock;
    private final Lock readLock;
    private final Lock writeLock;
    private final Condition full;
    private final Condition empty;
    private final Queue<Integer> queue;
    private final int capacity;

    public BoundedBlockingQueue(int capacity) {
        this.lock = new ReentrantReadWriteLock();
        this.readLock = lock.readLock();
        this.writeLock = lock.writeLock();
        this.full = writeLock.newCondition();
        this.empty = writeLock.newCondition();
        this.queue = new LinkedList<>();
        this.capacity = capacity;
    }
    
    public void enqueue(int element) throws InterruptedException {
        writeLock.lock();
        try {
            while (queue.size() == capacity) {
                full.await();
            }
            queue.offer(element);
            empty.signal();
        } finally {
            writeLock.unlock();
        }
    }
    
    public int dequeue() throws InterruptedException {
        writeLock.lock();
        try {
            while (queue.size() == 0) {
                empty.await();
            }
            int head = queue.poll();
            full.signal();
            return head;
        } finally {
            writeLock.unlock();
        }
    }
    
    public int size() {
        readLock.lock();
        try {
            return queue.size();
        } finally {
            readLock.unlock();
        }
    }
}